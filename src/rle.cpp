#include <cstdio>
#include <iostream>

#include "rle.hpp"

void
RLEChunk::print_chunk(){
	for(int i = 0, count = 0; i < dim*dim; i++){
		if(i == voxels[count+1].coord){
			count++;
		}
		printf("%d ", voxels[count].type);
		if(!((i+1) % dim)) printf("\n");
	}
}

void
RLEChunk::insert(int coord, int type){
	voxels[rle_count].coord = coord;
	voxels[rle_count].type = type;
	rle_count++;
}

RLEChunk::RLEChunk(){
    this->voxels = NULL;
    rle_count = 0;
    dim = 0;
}

RLEChunk::RLEChunk(int dim){
	this->voxels = new IntervalNode[dim*dim*dim];
	this->dim = dim;
	this->rle_count = 0;
}

RLEChunk::RLEChunk(int* array, int dim){
    init(array,dim);
}

RLEChunk::~RLEChunk(){
	delete[] this->voxels;
}

void
RLEChunk::init(int* array, int dim){
    voxels = new IntervalNode[dim*dim*dim];
    this->dim = dim;
    rle_count = 0;

    IntervalNode curr = {0, array[0]};
    voxels[rle_count++] = curr;

    for(int i = 1; i < dim*dim*dim; i++){
        
        if(array[i] == curr.type)
            continue;

        curr.coord = i;
        curr.type = array[i];
        voxels[rle_count++] = curr;
    }

    if(curr.coord != 0) voxels[rle_count++] = curr;

    // add a "null terminating run"
    curr.coord = dim*dim*dim;
    curr.type = 0;
    voxels[rle_count++] = curr;
}
int
RLEChunk::coord_conv(glm::vec3 in){
    return in.x + in.y * dim + in.z *dim*dim;
}

glm::vec3
RLEChunk::coord_conv(int in){
    int x = in%dim;
    int y = (in%(dim*dim))/dim;
    int z = (in%(dim*dim*dim)/(dim*dim));
    return glm::vec3(x,y,z);
}

IntervalNode
RLEChunk::get_rle(int i){
    for(int j = 0; j < rle_count; j++){
        if(voxels[j].coord > i){
            return voxels[j-1];
        }
    }
    return voxels[rle_count];
}

std::vector<glm::vec3>
RLEChunk::less_naive(){
    std::vector<glm::vec3> verts;
    for(int i = 0; i < rle_count-1; i++){
        if(voxels[i].type != 0){

            // copies needed for safe modification
            IntervalNode curr = voxels[i];
            IntervalNode next = voxels[i+1];

            while(next.coord/dim > curr.coord/dim){

                // continues on to the next one
                // gen volume filling to end of the row
                std::vector<glm::vec3> vol = gen_volume(
                    coord_conv(curr.coord),
                    coord_conv(curr.coord/dim*dim)+glm::vec3(dim-1,0,0));
                verts.insert(verts.end(),vol.begin(),vol.end());

                // set coord to the start of next row
                curr.coord = curr.coord/dim*dim+dim;
            }

            // don't create a volume at the start of a row
            if(curr.coord == next.coord) continue;

            // generate remaining volume
            std::vector<glm::vec3> vol = gen_volume(
                coord_conv(curr.coord),
                coord_conv(next.coord)-glm::vec3(1,0,0));
            verts.insert(verts.end(),vol.begin(),vol.end());
        }
        // needs to still do something about final node
        // maybe add a "phantom node" after the last position?
    }
    return verts;
}

std::vector<glm::vec3>
RLEChunk::gen_mesh(){
    std::vector<glm::vec3> verts;

    for(int i = 0; i < rle_count-1; i++){
        if(voxels[i].type != 0){

            // copies needed for safe modification
            IntervalNode curr = voxels[i];
            IntervalNode next = voxels[i+1];

            // gen volume filling to end of the row
            if(coord_conv(curr.coord).x != 0.0 && next.coord/dim > curr.coord/dim){
                std::vector<glm::vec3> vol = gen_volume(
                    coord_conv(curr.coord),
                    coord_conv(curr.coord/dim*dim)+glm::vec3(dim-1,0,0));
                verts.insert(verts.end(),vol.begin(),vol.end());
                // set coord to the start of next row
                curr.coord = curr.coord/dim*dim+dim;
            }

            // fill volume in between
            if(next.coord/dim > curr.coord/dim){
                std::vector<glm::vec3> vol = gen_volume(
                    coord_conv(curr.coord),
                    coord_conv((next.coord-dim)/dim*dim)+glm::vec3(dim-1,0,0));
                verts.insert(verts.end(),vol.begin(),vol.end());
                curr.coord = next.coord/dim*dim;
            }

            // don't create a volume at the start of a row
            if(curr.coord != next.coord){
                // generate remaining volume
                std::vector<glm::vec3> vol = gen_volume(
                    coord_conv(curr.coord),
                    coord_conv(next.coord)-glm::vec3(1,0,0));
                verts.insert(verts.end(),vol.begin(),vol.end());
            }

            // needs to still do something about final node
            // maybe add a "phantom node" after the last position?
        }
    }
    return verts;
}

std::vector<glm::vec3>
add_square(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d){
    // takes four coplanar points and makes a square between them
    // points should be clockwise to generate correct normals

    std::vector<glm::vec3> mesh;
    glm::vec3 ac = c - a;
    glm::vec3 ab = b - a;
    glm::vec3 normal = glm::normalize(glm::cross(ab, ac));

    // nothing to see here
    mesh.push_back(a);
    mesh.push_back(normal);
    mesh.push_back(b);
    mesh.push_back(normal);
    mesh.push_back(c);
    mesh.push_back(normal);
    mesh.push_back(c);
    mesh.push_back(normal);
    mesh.push_back(d);
    mesh.push_back(normal);
    mesh.push_back(a);
    mesh.push_back(normal);

    return mesh;
}

std::vector<glm::vec3>
gen_volume(glm::vec3 a, glm::vec3 b){
    std::vector<glm::vec3> mesh;

    a = a - glm::vec3(0.5,0.5,0.5);
    b = b + glm::vec3(0.5,0.5,0.5);

    // get the other vertices
    double dx = b.x - a.x;
    double dy = b.y - a.y;
    double dz = b.z - a.z;
    glm::vec3 c = a + glm::vec3(dx,0,0);
    glm::vec3 d = a + glm::vec3(0,dy,0);
    glm::vec3 e = a + glm::vec3(0,0,dz);
    glm::vec3 f = a + glm::vec3(dx,0,dz);
    glm::vec3 g = a + glm::vec3(dx,dy,0);
    glm::vec3 h = a + glm::vec3(0,dy,dz);

    // some of these need to be reversed to make normals correct
    std::vector<glm::vec3> s0 = add_square(e,h,d,a);
    std::vector<glm::vec3> s1 = add_square(e,f,c,a);
    std::vector<glm::vec3> s2 = add_square(d,g,c,a);
    std::vector<glm::vec3> s3 = add_square(g,c,f,b);
    std::vector<glm::vec3> s4 = add_square(b,f,e,h);
    std::vector<glm::vec3> s5 = add_square(b,g,d,h);

    mesh.insert(mesh.end(),s0.begin(),s0.end());
    mesh.insert(mesh.end(),s1.begin(),s1.end());
    mesh.insert(mesh.end(),s2.begin(),s2.end());
    mesh.insert(mesh.end(),s3.begin(),s3.end());
    mesh.insert(mesh.end(),s4.begin(),s4.end());
    mesh.insert(mesh.end(),s5.begin(),s5.end());

    return mesh;
}
