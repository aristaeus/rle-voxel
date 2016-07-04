#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <map>

#include <glm/glm.hpp>

#include <wrap.hpp>

class BaseComponent{
    public:
    glm::vec3 position;
    void update();
};

class Game{
    public:
    std::map<int,BaseComponent> base_components;
    void update();
};

#endif
