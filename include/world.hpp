#ifndef WORLD_HPP
#define WORLD_HPP

#include "procgen.hpp"
#include "rle.hpp"

class Game;

class World{
    std::map<int,RLEChunk> chunks;
    Game* game;
    int dim;
    Terrain terrain_noise;
    glm::vec3 prev_chunk;

    public:
    void init(int dim, Game* game);
    void gen_chunk(glm::vec3 pos, int id);
    glm::vec3 chunk_pos(glm::vec3 pos);
    void update_chunks();
};

#endif
