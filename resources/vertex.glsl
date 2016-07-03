#version 130
  
in vec3 position;
in vec3 norm;

out vec3 norms;
out vec3 pos;

uniform mat4 transform;

void main()
{
    norms = norm;
    pos = position;
    gl_Position = transform*vec4(position, 1.0);
}
