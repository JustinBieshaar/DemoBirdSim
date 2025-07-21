#version 400 core

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec2 in_textureCoords;

out vec2 pass_textureCoords;
out vec3 pass_surfaceNormal;
out vec3 pass_toLightFactor;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

uniform vec3 u_lightPosition;
uniform int u_repeat;

void main()
{
    pass_textureCoords = in_textureCoords * u_repeat;
    
    vec4 worldPosition = u_model * vec4(in_position, 1.0);
    gl_Position = u_projection * u_view * worldPosition;

    pass_surfaceNormal = (u_model * vec4(in_normal, 0.0)).xyz;
    pass_toLightFactor = u_lightPosition - worldPosition.xyz;
}