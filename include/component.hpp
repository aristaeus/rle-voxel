#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <map>

#include <glm/glm.hpp>
#include <SFML/OpenGL.hpp>

#include "wrap.hpp"

class BaseComponent{
    public:
    glm::vec3 position;
    void update();
};

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
    BaseComponent* base;
  public:
    void init(GLfloat* vertices, int size, GLuint uniform, BaseComponent* base);
    void draw(glm::mat4 proj);
};

class Game;

class GLProgram{
    Camera* cam;
    Game* game;
    public:
    std::map<int,VAO> vaos;
    GLuint prog;
    void init(Game* game, sf::Window* window);
    void add_vao(GLfloat* verts, int size, int id);
    void update();
    ~GLProgram();
};

class Game{
    public:
    std::map<int,BaseComponent> base_components;
    GLProgram vaos;
    void init(sf::Window* window);
    void update();
    int new_component(glm::vec3 pos);
};

#endif
