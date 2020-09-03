#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Engine
{

struct Transform
{
	glm::vec3 position{ 0.0f, 0.0f, 0.0f };
	glm::vec3 rotation{ 0.0f, 0.0f, 0.0f };
	glm::vec3 scale{ 1.0f, 1.0f, 1.0f };

	glm::mat4 genModelMatrix() const
	{
		glm::mat4 model(1.0f);

		model = glm::translate(model, position);
		model = glm::rotate(model, glm::radians(rotation.x), { 1.0f, 0.0f, 0.0f });
		model = glm::rotate(model, glm::radians(rotation.y), { 0.0f, 1.0f, 0.0f });
		model = glm::rotate(model, glm::radians(rotation.z), { 0.0f, 0.0f, 1.0f });
		model = glm::scale(model, scale);

		return model;
	}
};

}

#endif // !__TRANSFORM_H__
