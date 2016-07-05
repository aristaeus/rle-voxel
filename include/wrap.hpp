#ifndef WRAP_HPP
#define WRAP_HPP

#include <vector>

#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>

#include <glm/glm.hpp>

class Renderer{
    sf::Window window;
    bool run;
  public:
    Renderer();
    ~Renderer();
    void draw();
    bool is_open();
    sf::Window* get_window();
};

#endif
