#ifndef __SCENE_TESTS_H__
#define __SCENE_TESTS_H__

#include "../Engine/IScene.h"
#include "../Engine/Texture.h"
#include "../Engine/ShaderProgram.h"
#include "../Engine/VertexBuffer.h"
#include "../Engine/Camera.h"
#include "../Engine/Transform.h"

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

	struct Pair
	{
		Engine::Texture texture;
		Engine::Transform transform;
	};

	Engine::Camera m_camera;

	Engine::Texture m_marbleTexture;
	Engine::Texture m_metalTexture;
	Engine::Texture m_grassTexture;
	Engine::Texture m_windowTexture;

	Engine::ShaderProgram m_simpleShader;

	Engine::VertexBuffer m_cubeVertexBuffer;
	Engine::VertexBuffer m_planeVertexBuffer;

	Engine::Transform m_cube1;
	Engine::Transform m_cube2;
	Engine::Transform m_ground;

	Engine::Transform m_grass1;
	Engine::Transform m_grass2;
	Engine::Transform m_grass3;

	Engine::Transform m_window1;
	Engine::Transform m_window2;
	Engine::Transform m_window3;
	Engine::Transform m_window4;
};

#endif // !__SCENE_TESTS_H__
