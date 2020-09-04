#ifndef __SCENE_8_H__
#define __SCENE_8_H__

#include "../Engine/IScene.h"
#include "../Engine/ShaderProgram.h"
#include "../Engine/VertexBuffer.h"
#include "../Engine/Texture.h"
#include "../Engine/Camera.h"
#include "../Engine/Transform.h"
#include "../Engine/Texture.h"

#include <glm/glm.hpp>

class Scene_8 : public Engine::IScene
{
public:
	virtual void update(float deltaTime) override final;

	virtual void onEnter() override final;
	virtual void onExit() override final;
private:
	struct Material
	{
		Engine::Texture	diffuse;
		Engine::Texture	specular;

		float shininess;
	};

	struct LightMaterial
	{
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};

	Engine::ShaderProgram m_cubeShader;
	Engine::ShaderProgram m_lightShader;

	Engine::VertexBuffer m_vao;

	Engine::Camera m_camera;

	Engine::Transform m_cube;
	Engine::Transform m_light;

	Material m_cubeMaterial;

	LightMaterial m_lightMaterial;
};

#endif // !__SCENE_8_H__
