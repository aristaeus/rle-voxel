#ifndef WORLD_HPP
#define WORLD_HPP

#include "rle.hpp"

class World{
    RLEChunk chunks [16];
    int dim;

    public:
    void init(Renderer* render, int dim);
};

#endif
