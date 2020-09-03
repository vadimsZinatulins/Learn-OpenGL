#version 330 core

in vec3 colorFromVertex;

out vec4 fragmentColor;

void main()
{
    fragmentColor = vec4(colorFromVertex, 1.0f);
} 