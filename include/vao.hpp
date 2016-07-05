#ifndef VAO_HPP
#define VAO_HPP

#include <map>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>

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

class BaseComponent;

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

#endif
