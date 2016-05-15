#include <fstream>
#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>
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
	window.create(sf::VideoMode(800,600), "stuff");
	window.setVerticalSyncEnabled(true);

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

	glm::mat4 trans;
	trans = glm::translate(trans, glm::vec3(0.5,0.5,0.0));

	GLuint transform = glGetUniformLocation(prog, "transform");
	glUniformMatrix4fv(transform, 1, GL_FALSE, glm::value_ptr(trans));

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
