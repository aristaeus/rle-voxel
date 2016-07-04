#include "world.hpp"

void
World::init(Renderer* render, int dim, Game* game){
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
        BaseComponent base;
        game->base_components.insert(std::pair<int,BaseComponent>(i,base));
        game->base_components[i].position = pos;
	    render->add_mesh((GLfloat*)verts.data(), 3*verts.size(),&(game->base_components[i]));
    }
}
