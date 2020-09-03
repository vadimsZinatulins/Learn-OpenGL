#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <glm/glm.hpp>

namespace Engine
{

struct Camera
{
	glm::vec3 position{ glm::vec3{ 0.0f, 2.0f,  3.0f } };
	glm::vec3 front{ glm::vec3{ 0.0f, 0.0f, -1.0f } };
	glm::vec3 up{ glm::vec3{ 0.0f, 1.0f,  0.0f } };

	float yaw{ -90.0f };
	float pitch{ -25.0f };

	float moveSpeed = 8.0f;
	float rotationSpeed = 64.0f;

	glm::mat4 getView() const; /*{ return glm::lookAt(position, position + front, up); }*/
	void update(float deltaTime);
	/*{
		Engine::InputManager &input = Engine::InputManager::getInstance();

		Engine::MouseCoords mouseCoordsRel = input.getMouseCoordsRel();
		m_camera.yaw += mouseCoordsRel.x * deltaTime * m_camera.rotationSpeed;
		m_camera.pitch -= mouseCoordsRel.y * deltaTime * m_camera.rotationSpeed;

		if(m_camera.pitch > 89.0f)
			m_camera.pitch = 89.0f;
		else if(m_camera.pitch < -89.0f)
			m_camera.pitch = -89.0f;

		glm::vec3 direction;
		direction.x = glm::cos(glm::radians(m_camera.yaw)) * glm::cos(glm::radians(m_camera.pitch));
		direction.y = glm::sin(glm::radians(m_camera.pitch));
		direction.z = glm::sin(glm::radians(m_camera.yaw)) * glm::cos(glm::radians(m_camera.pitch));
		m_camera.front = glm::normalize(direction);

		float speed = m_camera.moveSpeed * deltaTime;
		m_camera.position += input.isKeyDown(KEY_W) * speed * m_camera.front + input.isKeyDown(KEY_S) * speed * m_camera.front * -1.0f;
		m_camera.position += input.isKeyDown(KEY_D) * speed * glm::normalize(glm::cross(m_camera.front, m_camera.up)) + input.isKeyDown(KEY_A) * speed * glm::normalize(glm::cross(m_camera.up, m_camera.front));
	}*/
};

}

#endif // !__CAMERA_H__
