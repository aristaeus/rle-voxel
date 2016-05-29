#version 130

in vec3 norms;
in vec3 pos;

out vec4 color;

void main()
{
    vec3 colours = vec3(1.0, 0.5, 0.2);
    vec3 dir = normalize(vec3(-10, 5, -8));
    float phong = dot(norms, dir);
    color = vec4(phong*colours, 1.0f);
} 
