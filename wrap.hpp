#ifndef WRAP_HPP
#define WRAP_HPP

#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>

class renderer{
	sf::Window window;
	bool run;
	GLuint vbo;
	GLuint vshad;
	GLuint fshad;
	GLuint prog;
	GLuint vao;
  public:
	renderer();
	void draw();
	bool is_open();
};

#endif
