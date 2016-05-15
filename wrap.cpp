#include <cmath>
#include <cstdio>
#include <fstream>
#include <string>

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "wrap.hpp"

GLuint load_shader(const char* filename, GLenum type){
	/* load source into memory */
	std::fstream file;
	std::string src_str;

	file.open(filename);
	std::string line;
	if(file.is_open()){
		while(getline(file,line)) src_str += line + '\n';
	} else printf("error loading %s\n", filename);

	const char* src = src_str.c_str();

	/* pass source to OpenGL */
	GLuint shad = glCreateShader(type);
	glShaderSource(shad, 1, &src, NULL);
	glCompileShader(shad);

	/* check for errors */
	GLint status = 0;
	glGetShaderiv(shad, GL_COMPILE_STATUS, &status);
	if(!status){
		GLchar error[512];
		glGetShaderInfoLog(shad, 512, NULL, error);
    	printf("Shader error: %s\n", error);
	}
	
	return shad;
}

GLuint load_program(const char* vfile, const char* ffile){
	/* load shaders */
	GLuint vshad = load_shader(vfile, GL_VERTEX_SHADER);
	GLuint fshad = load_shader(ffile, GL_FRAGMENT_SHADER);

	/* create program */
	GLuint prog = glCreateProgram();
	glAttachShader(prog, vshad);
	glAttachShader(prog, fshad);
	glLinkProgram(prog);

	/* error checking */


	/* cleanup */
	glDeleteShader(vshad);
	glDeleteShader(fshad);

	return prog;
}

renderer::renderer(){
	run = true;

	sf::ContextSettings s;
	s.antialiasingLevel = 4;

	window.create(sf::VideoMode(800,600), "stuff", sf::Style::Default, s);
	window.setVerticalSyncEnabled(true);

	s = window.getSettings();
	printf("GL: %d.%d\nAA: %d\nDB:%d\nSB: %d\n", s.majorVersion, s.minorVersion, s.antialiasingLevel, s.depthBits, s.stencilBits);

	// OpenGL stuff

	glewInit();

	prog = load_program("vertex.glsl", "fragment.glsl");
	glUseProgram(prog);
	
	GLfloat vertices[] = {
    	-0.5f, -0.5f, 0.0f,
     	 0.5f, -0.5f, 0.0f,
     	 0.0f,  0.5f, 0.0f
	};



	/* gen buffer data */
	glGenBuffers(1, &this->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	/* gen vao */
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	/* index, size of att, type, normalise, stride, offset */
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(GLfloat),(GLvoid*)0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	// get camera
	cam = new FPSCam(&window);
}

renderer::~renderer(){
	delete cam;
}

void renderer::draw(){
	sf::Event event;
	while(window.pollEvent(event)){
		if(event.type == sf::Event::Closed){
			window.close();
			run = false;
		}
	}

	// OpenGL stuff
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// transformation matrix
	glm::mat4 trans;
	trans = glm::translate(trans, glm::vec3(0.0,0.0,0.0));

	// view (camera) matrix
	glm::mat4 view = cam->get_cam();

	// projection matrix
	glm::mat4 proj;
	proj = glm::perspective(45.0, 800*1.0/600, 0.1, 100.0);

	GLuint transform = glGetUniformLocation(prog, "transform");

	// pass to shader
	glm::mat4 mvp = proj * view * trans;
	glUniformMatrix4fv(transform, 1, GL_FALSE, glm::value_ptr(mvp));

	glUseProgram(prog);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0); 


	window.display();
}

bool
renderer::is_open(){
	return run;
}

glm::mat4
Camera::get_cam(){
	this->update();
	return glm::lookAt(pos, target, up);
}

FPSCam::FPSCam(sf::Window* win){
	pos = glm::vec3(0.0,0.0,3.0);
	target = glm::vec3(0.0,0.0,0.0);
	up = glm::vec3(0.0,1.0,0.0);

	window = win;

	rotx = 0;
	roty = 0;
}

void FPSCam::
update(){
	double dt = 0.1;


	// update rotation with mouse
	sf::Vector2i mos = sf::Mouse::getPosition(*window);
	sf::Mouse::setPosition(sf::Vector2i(0,0), *window);

	rotx -= mos.x/500.0;

	// update position from keyboard input
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
		pos.x += 1*dt*sin(rotx);
		pos.z += 1*dt*cos(rotx);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
		pos.x -= 1*dt*sin(rotx);
		pos.z -= 1*dt*cos(rotx);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
		pos.x += 1*dt*cos(rotx);
		pos.z -= 1*dt*sin(rotx);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
		pos.x -= 1*dt*cos(rotx);
		pos.z += 1*dt*sin(rotx);
	}

	target = glm::vec3(pos.x+sin(rotx), pos.y, pos.z+cos(rotx));
}
