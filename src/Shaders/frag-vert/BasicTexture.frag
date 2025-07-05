#version 330 core

in vec2 pass_textureCoords;

out vec4 out_Color;

uniform sampler2D u_textureSampler;

void main()
{
    out_Color = texture(u_textureSampler, pass_textureCoords);
}