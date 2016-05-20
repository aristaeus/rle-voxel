#ifndef WRAP_HPP
#define WRAP_HPP

#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>

#include <glm/glm.hpp>

class Camera{   // Camera for OpenGL
  protected:
    glm::vec3 pos;
    glm::vec3 target;
    glm::vec3 up;
    virtual void update() {};   // Update pos target and up
  public:
    virtual ~Camera() {};
    glm::mat4 get_cam();        // Return camera matrix
};

class FPSCam: public Camera{
    void update();
    double rotx;
    double roty;
    sf::Window* window;
  public:
    FPSCam(sf::Window* win);
    ~FPSCam() {};
};

class VAO{
    GLuint vbo;
    GLuint vao;
    GLuint uni;
    int size;
  public:
    void init(GLfloat* vertices, int size, GLuint uniform);
    void draw(glm::mat4 proj);
};

class renderer{
    sf::Window window;
    Camera* cam;
    bool run;
    GLuint prog;
    VAO vao;
  public:
    renderer();
    ~renderer();
    void draw();
    bool is_open();
    void add_mesh(GLfloat* verts, int size);
};

#endif
