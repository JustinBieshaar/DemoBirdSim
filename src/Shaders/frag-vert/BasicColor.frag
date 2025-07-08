#version 400 core

in vec3 pass_surfaceNormal;
in vec3 pass_toLightFactor;

out vec4 out_Color;

uniform vec3 u_lightColor;

void main()
{
    vec3 unitNormal = normalize(pass_surfaceNormal);
    vec3 unitLightVector = normalize(pass_toLightFactor);

    float d = dot(unitNormal, unitLightVector);
    float brightness = max(d, 0.1);
    vec3 diffuse = brightness * u_lightColor;

    out_Color = vec4(diffuse, 1.0);
}