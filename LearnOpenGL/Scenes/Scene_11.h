#ifndef __SCENE_11_H__
#define __SCENE_11_H__

#include "../Engine/IScene.h"
#include "../Engine/ShaderProgram.h"
#include "../Engine/VertexBuffer.h"
#include "../Engine/Texture.h"
#include "../Engine/Camera.h"
#include "../Engine/Transform.h"
#include "../Engine/Texture.h"

#include <glm/glm.hpp>

#define NUM_CUBES_SCENE_11 25
#define NUM_POINT_LIGHTS_SCENE_11 4

class Scene_11 : public Engine::IScene
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

	struct DirLightMaterial
	{
		glm::vec3 direction;

		LightMaterial material;
	};

	struct PointLightMaterial
	{
		float constant;
		float linear;
		float quadratic;

		LightMaterial material;
	};

	struct SpotLightMaterial
	{
		float innerCutOff;
		float outerCutOff;

		float constant;
		float linear;
		float quadratic;

		LightMaterial material;
	};

	Engine::ShaderProgram m_cubeShader;
	Engine::ShaderProgram m_lightShader;

	Engine::VertexBuffer m_vao;

	Engine::Camera m_camera;

	Engine::Transform m_cubes[NUM_CUBES_SCENE_11];
	Engine::Transform m_pointLights[NUM_POINT_LIGHTS_SCENE_11];

	Material m_cubeMaterial;

	DirLightMaterial m_dirLightMaterial;
	PointLightMaterial m_pointLightMaterials[NUM_POINT_LIGHTS_SCENE_11];
	SpotLightMaterial m_spotLightMaterial;
};

#endif // !__SCENE_11_H__
