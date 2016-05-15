#ifndef WRAP_HPP
#define WRAP_HPP

#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>

#include <glm/glm.hpp>

class Camera{
  protected:
	glm::vec3 pos;
	glm::vec3 target;
	glm::vec3 up;
  	virtual void update() {};
  public:
	glm::mat4 get_cam();
};

class FPSCam: public Camera{
	sf::Window* window;
	// void update();
  public:
	FPSCam(sf::Window* win);
};

class renderer{
	sf::Window window;
	Camera* cam;
	bool run;
	GLuint vbo;
	GLuint prog;
	GLuint vao;
  public:
	renderer();
	void draw();
	bool is_open();
};

#endif
