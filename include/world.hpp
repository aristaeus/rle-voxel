#ifndef WORLD_HPP
#define WORLD_HPP

#include "component.hpp"
#include "rle.hpp"

class World{
    RLEChunk chunks [16];
    int dim;

    public:
    void init(int dim, Game* game);
};

#endif
