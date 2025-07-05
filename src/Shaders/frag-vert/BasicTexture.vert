#version 330 core

in vec3 in_position;
in vec2 in_textureCoords;

out vec2 pass_textureCoords;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
    gl_Position = u_Projection * u_View * u_Model * vec4(in_position, 1.0);
    pass_textureCoords = in_textureCoords;
}