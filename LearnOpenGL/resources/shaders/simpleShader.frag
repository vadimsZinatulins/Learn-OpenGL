#version 330 core

in vec2 fragUVCoord;

out vec4 fragmentColor;

uniform sampler2D textureSample;

void main() 
{
    fragmentColor = texture(textureSample, fragUVCoord);
}