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
    
    // second triangle
    mesh.push_back(v1);
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
