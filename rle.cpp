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

std::vector<GLfloat>
add_square(double xs, double ys, double zs, double xe, double ye, double ze){
    std::vector<GLfloat> mesh;

    // first triangle
    mesh.push_back(xs);
    mesh.push_back(ys);
    mesh.push_back(zs);
    
    mesh.push_back(xs);
    mesh.push_back(ye);
    mesh.push_back(ze);
    
    mesh.push_back(xe);
    mesh.push_back(ye);
    mesh.push_back(ze);

    // second triangle
    mesh.push_back(xs);
    mesh.push_back(ys);
    mesh.push_back(zs);
    
    mesh.push_back(xe);
    mesh.push_back(ys);
    mesh.push_back(zs);
    
    mesh.push_back(xe);
    mesh.push_back(ye);
    mesh.push_back(ze);

    return mesh;
}
