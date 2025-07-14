#version 400 core

out vec4 out_Color;

//uniform vec3 u_color; // TODO Pass desired wireframe color

void main()
{
    out_Color = vec4(0.0, 0.0, 0.0, 1.0); // black lines
}