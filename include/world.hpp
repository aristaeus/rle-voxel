#ifndef WORLD_HPP
#define WORLD_HPP

#include "rle.hpp"

class Game;

class World{
    RLEChunk chunks [16];
    Game* game;
    int dim;

    public:
    void init(int dim, Game* game);
    void gen_chunk(glm::vec3 pos, int id);
};

#endif
