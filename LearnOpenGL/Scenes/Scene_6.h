#ifndef __SCENE_6_H__
#define __SCENE_6_H__

#include "../Engine/IScene.h"
#include "../Engine/ShaderProgram.h"
#include "../Engine/VertexBuffer.h"
#include "../Engine/Texture.h"
#include "../Engine/Camera.h"
#include "../Engine/Transform.h"

#include <glm/glm.hpp>

class Scene_6 : public Engine::IScene
{
public:
	virtual void update(float deltaTime) override final;

	virtual void onEnter() override final;
	virtual void onExit() override final;
private:
	Engine::ShaderProgram m_cubeShader;
	Engine::ShaderProgram m_lightShader;

	Engine::VertexBuffer m_vao;

	Engine::Camera m_camera;

	Engine::Transform m_cube;
	Engine::Transform m_light;

	glm::vec3 m_lightColor;
	glm::vec3 m_cubeColor;
};

#endif // !__SCENE_6_H__
