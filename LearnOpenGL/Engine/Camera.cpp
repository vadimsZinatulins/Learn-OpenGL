#include "Camera.h"
#include "InputManager.h"

#include <glm/gtc/matrix_transform.hpp>

glm::mat4 Engine::Camera::getView() const
{
	return glm::lookAt(position, position + front, up);
}

void Engine::Camera::update(float deltaTime)
{
	InputManager &input = InputManager::getInstance();

	MouseCoords mouseCoordsRel = input.getMouseCoordsRel();
	yaw += mouseCoordsRel.x * deltaTime * rotationSpeed;
	pitch -= mouseCoordsRel.y * deltaTime * rotationSpeed;

	if(pitch > 89.0f)
		pitch = 89.0f;
	else if(pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 direction;
	direction.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
	direction.y = glm::sin(glm::radians(pitch));
	direction.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
	front = glm::normalize(direction);

	float speed = moveSpeed * deltaTime;
	position += input.isKeyDown(KEY_W) * speed * front + input.isKeyDown(KEY_S) * speed * front * -1.0f;
	position += input.isKeyDown(KEY_D) * speed * glm::normalize(glm::cross(front, up)) + input.isKeyDown(KEY_A) * speed * glm::normalize(glm::cross(up, front));
}
