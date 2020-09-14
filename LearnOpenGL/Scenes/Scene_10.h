#ifndef __SCENE_10_H__
#define __SCENE_10_H__

#include "../Engine/IScene.h"
#include "../Engine/ShaderProgram.h"
#include "../Engine/VertexBuffer.h"
#include "../Engine/Texture.h"
#include "../Engine/Camera.h"
#include "../Engine/Transform.h"
#include "../Engine/Texture.h"

#include <glm/glm.hpp>

#define NUM_CUBES_SCENE_10 15

class Scene_10 : public Engine::IScene
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
		
		float innerCutOff;
		float outerCutOff;

		float constant;
		float linear;
		float quadratic;
	};

	Engine::ShaderProgram m_cubeShader;

	Engine::VertexBuffer m_vao;

	Engine::Camera m_camera;

	Engine::Transform m_cubes[NUM_CUBES_SCENE_10];

	Material m_cubeMaterial;

	LightMaterial m_lightMaterial;
};

#endif // !__SCENE_10_H__
