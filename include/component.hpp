#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <map>

#include <glm/glm.hpp>

#include "vao.hpp"
#include "world.hpp"
#include "wrap.hpp"

class BaseComponent{
    public:
    glm::vec3 position;
    void update();
};

class Game{
    public:
    std::map<int,BaseComponent> base_components;
    std::map<int,BaseComponent>::iterator player;
    GLProgram vaos;
    World chunks;
    void init(sf::Window* window);
    void update();
    int new_component(glm::vec3 pos);
};

#endif
