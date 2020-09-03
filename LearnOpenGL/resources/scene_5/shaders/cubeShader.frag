#version 330 core

out vec4 fragmentColor;

uniform vec3 cubeColor;
uniform vec3 lightColor;

void main()
{
    fragmentColor = vec4(lightColor * cubeColor, 1.0);
}
