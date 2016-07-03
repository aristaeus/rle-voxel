#include "world.hpp"

void
World::init(Renderer* render, int dim){
    this->dim = dim;
	int array[] = {0, 1, 1, 1, 1,
	               1, 1, 0, 0, 0,
	               0, 0, 1, 1, 1,
	               0, 0, 1, 1, 1,
	               0, 0, 1, 1, 1,
	               1, 1 };

    for(int i = 0; i < dim*dim; i++){
        chunks[i].init(array,dim);
        std::vector<glm::vec3> verts = chunks[i].less_naive();
        glm::vec3 pos ((i%dim)*dim, 0, (i/dim)*dim);
	    render->add_mesh((GLfloat*)verts.data(), 3*verts.size(),pos);
    }
}
