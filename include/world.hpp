#ifndef WORLD_HPP
#define WORLD_HPP

#include "rle.hpp"

class World{
    rle_chunk chunks [16];

    public:
    void init(renderer* render);
};

#endif
