#include <cstdio>

#include "rle.hpp"

void
rle_chunk::print_chunk(){
	for(int i = 0, count = 0; i < dim*dim; i++){
		if(i == voxels[count+1].coord){
			count++;
		}
		printf("%d ", voxels[count].type);
		if(!((i+1) % dim)) printf("\n");
	}
}

void
rle_chunk::insert(int coord, int type){
	voxels[rle_count].coord = coord;
	voxels[rle_count].type = type;
	rle_count++;
}

rle_chunk::rle_chunk(int dim){
	this->voxels = new int_node[dim*dim*dim];
	this->dim = dim;
	this->rle_count = 0;
}

rle_chunk::~rle_chunk(){
	delete[] this->voxels;
}

int
rle_chunk::coord_conv(glm::vec3 in){
    return in.x + in.y * dim + in.z *dim*dim;
}

glm::vec3
rle_chunk::coord_conv(int in){
    int x = in%dim;
    int y = ((in-x)%(dim*dim))/dim;
    int z = ((in-x-y)%(dim*dim*dim)/(dim*dim));
    return glm::vec3(x,y,z);
}

int_node
rle_chunk::get_rle(int i){
    for(int j = 0; j < rle_count; j++){
        if(voxels[j].coord > i){
            return voxels[j-1];
        }
    }
    return voxels[rle_count];
}

std::vector<glm::vec3>
rle_chunk::naive_mesh(){
    std::vector<glm::vec3> verts;
    for(int i = 0; i < dim*dim*dim; i++){
        if(get_rle(i).type != 0){
            glm::vec3 coord = coord_conv(i);
            std::vector<glm::vec3> cube = add_cube(coord.x, coord.y, coord.z);
	        verts.insert(verts.begin(), cube.begin(), cube.end());
        }
    }
    return verts;
}

std::vector<glm::vec3>
rle_chunk::less_naive(){
    std::vector<glm::vec3> verts;
    for(int i = 0; i < rle_count; i++){
        if(voxels[i].type != 0){
            // glm::vec3 coord1 = coord_conv(voxels[i].coord);
            // glm::vec3 coord2;
            if(voxels[i+1].coord/5 > voxels[i].coord/5){
                
            } else {
                
            }
        }
    }
    return verts;
}

std::vector<glm::vec3>
add_square(double xs, double ys, double zs, double xe, double ye, double ze){
    std::vector<glm::vec3> mesh;

    // get points
    glm::vec3 v1(xs, ys, zs);
    glm::vec3 v2(xe, ye, ze);
    glm::vec3 v3;
    glm::vec3 v4;

    if(fabs(xe-xs) < 0.001){
        v3 = glm::vec3(xs, ys, ze);
        v4 = glm::vec3(xs, ye, zs);
    } else {
        v3 = glm::vec3(xs, ye, ze);
        v4 = glm::vec3(xe, ys, zs);
    }
    //normal
    glm::vec3 norm = glm::cross(v3-v1, v4-v1);

    // first triangle
    mesh.push_back(v1);
    mesh.push_back(glm::normalize(norm));
    mesh.push_back(v2);
    mesh.push_back(glm::normalize(norm));
    mesh.push_back(v3);
    mesh.push_back(glm::normalize(norm));
    
    // second triangle mesh.push_back(v1);
    mesh.push_back(glm::normalize(norm));
    mesh.push_back(v2);
    mesh.push_back(glm::normalize(norm));
    mesh.push_back(v4);
    mesh.push_back(glm::normalize(norm));

    return mesh;
}

std::vector<glm::vec3>
add_cube(double x, double y, double z){
    double r = 0.5;
    
	std::vector<glm::vec3> verts = add_square(x+r, y-r, z+r, x-r, y-r, z-r);
	std::vector<glm::vec3> verts2 = add_square(x-r, y-r, z-r, x+r, y+r, z-r);
	std::vector<glm::vec3> verts3 = add_square(x-r, y-r, z-r, x-r, y+r, z+r);
	std::vector<glm::vec3> verts4 = add_square(x-r, y+r, z-r, x+r, y+r, z+r);
	std::vector<glm::vec3> verts5 = add_square(x-r, y-r, z+r, x+r, y+r, z+r);
	std::vector<glm::vec3> verts6 = add_square(x+r, y-r, z-r, x+r, y+r, z+r);
	verts.insert(verts.begin(), verts2.begin(), verts2.end());
	verts.insert(verts.begin(), verts3.begin(), verts3.end());
	verts.insert(verts.begin(), verts4.begin(), verts4.end());
	verts.insert(verts.begin(), verts5.begin(), verts5.end());
	verts.insert(verts.begin(), verts6.begin(), verts6.end());

	return verts;
}

std::vector<glm::vec3>
add_square(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d){
    // takes four coplanar points and makes a square between them

    std::vector<glm::vec3> mesh;
    glm::vec3 ac = c - a;
    glm::vec3 ab = b - a;
    glm::vec3 normal = -glm::normalize(glm::cross(ab, ac));
    // normal.x = fabs(normal.x);
    // normal.y = fabs(normal.y);
    // normal.z = fabs(normal.z);

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
    double dx = b.x - a.x;
    double dy = b.y - a.y;
    double dz = b.z - a.z;

    std::vector<glm::vec3> mesh;
    glm::vec3 c = a + glm::vec3(dx,0,0);
    glm::vec3 d = a + glm::vec3(0,dy,0);
    glm::vec3 e = a + glm::vec3(0,0,dz);
    glm::vec3 f = a + glm::vec3(dx,0,dz);
    glm::vec3 g = a + glm::vec3(dx,dy,0);
    glm::vec3 h = a + glm::vec3(0,dy,dz);

    std::vector<glm::vec3> s0 = add_square(a,d,h,e);
    std::vector<glm::vec3> s1 = add_square(a,c,f,e);
    std::vector<glm::vec3> s2 = add_square(a,c,g,d);
    std::vector<glm::vec3> s3 = add_square(b,f,c,g);
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
