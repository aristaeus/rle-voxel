#include <random>

#include "component.hpp"
#include "world.hpp"

void
World::init(int dim, Game* game){
    this->dim = dim;
    this->game = game;

    for(int i = 0; i < dim*dim; i++){
        glm::vec3 pos ((i%dim)*dim, 0, (i/dim)*dim);
	    gen_chunk(pos,i);
    }
}

void
World::gen_chunk(glm::vec3 pos, int id){
    int chunk[dim][dim][dim];
    std::mt19937 mt(id);
    std::uniform_int_distribution<int> dist(1,dim);

    for(int x = 0; x < dim; x++){
        for(int z = 0; z < dim; z++){
            // int height = 4;
            int height = dist(mt);
            for(int y = 0; y < dim; y++){
                if(y < height) chunk[x][y][z] = 1;
                else chunk[x][y][z] = 0;
            }
        }
    }

    chunks[id].init((int*)chunk, dim);
    std::vector<glm::vec3> verts = chunks[id].less_naive();
    int comp_id = game->new_component(pos);
	game->vaos.add_vao((GLfloat*)verts.data(), 3*verts.size(), comp_id);
}
