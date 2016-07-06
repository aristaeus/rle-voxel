#include <iostream>
#include <random>

#include "component.hpp"
#include "world.hpp"

void
World::init(int dim, Game* game){
    this->dim = dim;
    this->game = game;

    int num_chunk = 3;
    for(int i = 0; i < num_chunk*num_chunk; i++){
        glm::vec3 pos ((i%num_chunk)*dim, 0, (i/num_chunk)*dim);
	    gen_chunk(pos,i);
    }
    prev_chunk = glm::vec3(0,0,0);
}

void
World::gen_chunk(glm::vec3 pos, int id){
    int chunk[dim][dim][dim];
    std::mt19937 mt(id);
    std::uniform_int_distribution<int> dist(1,dim);

    for(int x = 0; x < dim; x++){
        for(int z = 0; z < dim; z++){
            // int height = 4;
            // int height = dist(mt);

            // WHY IS IT BACKWARDS
            float height = terrain_noise.get_value(pos+glm::vec3(z,0,x));
            for(int y = 0; y < dim; y++){
                if(y < height) chunk[x][y][z] = 1;
                else chunk[x][y][z] = 0;
            }
        }
    }

    int comp_id = game->new_component(pos);
    chunks[comp_id].init((int*)chunk, dim);
    std::vector<glm::vec3> verts = chunks[comp_id].gen_mesh();
	game->vaos.add_vao((GLfloat*)verts.data(), 3*verts.size(), comp_id);
}

glm::vec3
World::chunk_pos(glm::vec3 pos){
    int x = pos.x/dim;
    int y = pos.y/dim;
    int z = pos.z/dim;

    return glm::vec3(x*dim, 0, z*dim);
}

void
World::update_chunks(){
    glm::vec3 curr = chunk_pos(game->player->second.position);

    if(curr == prev_chunk) return;
    prev_chunk = curr;

    // generate list of required chunks
    std::vector<glm::vec3> chunk_coords;
    int rad = 3;
    for(int i = -rad; i < rad; i++){
        for(int j = -rad; j < rad; j++){
            chunk_coords.push_back(glm::vec3(i*dim,0,j*dim)+curr);
        }
    }

    // remove old chunks
    for(auto it = chunks.begin(); it != chunks.end(); it++){
        bool needed = 0;
        for(int i = 0; i < chunk_coords.size(); i++){
            if(chunk_coords[i]==game->base_components[it->first].position)
                needed = 1;
        }
        if(!needed){
            game->vaos.vaos.erase(it->first);
            chunks.erase(it);
        }
    }

    // add new chunks
    for(int i = 0; i < chunk_coords.size(); i++){
        bool needed = 1;
        for(auto it = chunks.begin(); it != chunks.end(); it++){
            if(chunk_coords[i]==game->base_components[it->first].position)
                needed = 0;
        }
        if(needed)
            gen_chunk(chunk_coords[i],0);
    }
};
