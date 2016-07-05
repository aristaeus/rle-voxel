#ifndef PROCGEN_HPP
#define PROCGEN_HPP

#include <glm/glm.hpp>
#include <libnoise/noise.h>

class Terrain{
    noise::module::Perlin module;
    public:
    void init();
    double get_value(glm::vec3 p);
};

#endif
