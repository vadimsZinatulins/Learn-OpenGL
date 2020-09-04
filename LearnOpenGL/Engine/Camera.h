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

	glm::mat4 getView() const;
	void update(float deltaTime);
	void reset();
};

}

#endif // !__CAMERA_H__
