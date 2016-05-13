#ifndef WRAP_HPP
#define WRAP_HPP

#include <SFML/Window.hpp>

class renderer{
	sf::Window window;
	bool run;
  public:
	renderer();
	void draw();
	bool is_open();
};

#endif
