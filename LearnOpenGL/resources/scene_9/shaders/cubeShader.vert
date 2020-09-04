#version 330 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 vertexUvCoords;;

out vec3 normalFromVertex;
out vec3 fragmentPosition;
out vec2 uvCoordsFromVertex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(vertexPosition, 1.0);

    fragmentPosition = vec3(model * vec4(vertexPosition, 1.0));
    normalFromVertex = mat3(transpose(inverse(model))) * vertexNormal;
    uvCoordsFromVertex = vertexUvCoords;
}