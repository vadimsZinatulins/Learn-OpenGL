#ifndef __SCENE_TESTS_H__
#define __SCENE_TESTS_H__

#include "Engine/IScene.h"
#include "Engine/Texture.h"
#include "Engine/ShaderProgram.h"
#include "Engine/VertexBuffer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class SceneTests : public Engine::IScene
{
public:
	virtual void update(float deltaTime) override final;

	virtual void onEnter() override final;
	virtual void onExit() override final;
private:
	void renderCubes(glm::mat4 &view);
	void renderPlanes(glm::mat4 &view, glm::vec3 &camPosition);

	struct Camera
	{
		glm::vec3 position{ glm::vec3{ 0.0f, 2.0f,  3.0f } };
		glm::vec3 front{ glm::vec3{ 0.0f, 0.0f, -1.0f } };
		glm::vec3 up{ glm::vec3{ 0.0f, 1.0f,  0.0f } };

		float yaw{ -90.0f };
		float pitch{ -25.0f };

		float moveSpeed = 8.0f;
		float rotationSpeed = 64.0f;

		glm::mat4 getView() const { return glm::lookAt(position, position + front, up); }
	};

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

	struct Pair
	{
		Engine::Texture texture;
		Transform transform;
	};

	Camera m_camera;

	Engine::Texture m_marbleTexture;
	Engine::Texture m_metalTexture;
	Engine::Texture m_grassTexture;
	Engine::Texture m_windowTexture;

	Engine::ShaderProgram m_simpleShader;

	Engine::VertexBuffer m_cubeVertexBuffer;
	Engine::VertexBuffer m_planeVertexBuffer;

	Transform m_cube1;
	Transform m_cube2;
	Transform m_ground;

	Transform m_grass1;
	Transform m_grass2;
	Transform m_grass3;

	Transform m_window1;
	Transform m_window2;
	Transform m_window3;
	Transform m_window4;
};

#endif // !__SCENE_TESTS_H__
