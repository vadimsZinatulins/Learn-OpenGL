#version 330 core

in vec2 uvCoordFromVertex;

out vec4 fragmentColor;

uniform sampler2D tex1;
uniform sampler2D tex2;

void main()
{
    fragmentColor = mix(texture(tex1, uvCoordFromVertex), texture(tex2, uvCoordFromVertex), 0.2);
} 