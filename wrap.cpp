#include <GL/glew.h>

#include <iostream>

#include "wrap.hpp"

renderer::renderer(){
	run = true;
	window.create(sf::VideoMode(800,600), "stuff");
	window.setVerticalSyncEnabled(true);

	// OpenGL stuff

	glewInit();
	
	GLfloat vertices[] = {
    	-0.5f, -0.5f, 0.0f,
     	 0.5f, -0.5f, 0.0f,
     	 0.0f,  0.5f, 0.0f
	};

	char* vsrc = "#version 130\n \n in vec3 position; \n \n void main() \n { \n gl_Position = vec4(position.x, position.y, position.z, 1.0); \n }";

	char* fsrc = "#version 130 \n \n out vec4 color;\n \n void main()\n {\n color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n } \n";

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &this->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	vshad = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vshad, 1, &vsrc, NULL);
	glCompileShader(vshad);
	GLint status = 0;
	glGetShaderiv(vshad, GL_COMPILE_STATUS, &status);
	if(!status){
		GLchar infoLog[512];
		glGetShaderInfoLog(vshad, 512, NULL, infoLog);
    	std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << "\n";	
	}

	fshad = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fshad, 1, &fsrc, NULL);
	glCompileShader(fshad);
	glGetShaderiv(fshad, GL_COMPILE_STATUS, &status);
	if(!status){
		GLchar infoLog[512];
		glGetShaderInfoLog(fshad, 512, NULL, infoLog);
    	std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << "\n";	
	}

	prog = glCreateProgram();
	glAttachShader(prog, vshad);
	glAttachShader(prog, fshad);
	glLinkProgram(prog);

	glUseProgram(prog);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	
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
