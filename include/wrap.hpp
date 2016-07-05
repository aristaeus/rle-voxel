#ifndef WRAP_HPP
#define WRAP_HPP

#include <SFML/Window.hpp>

#include <glm/glm.hpp>

class SFWindow{
    sf::Window window;
    bool run;
  public:
    SFWindow();
    ~SFWindow();
    void draw();
    bool is_open();
    sf::Window* get_window();
};

#endif
