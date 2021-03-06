#include "Scene_10.h"
#include "../Shapes/CubeShape.h"
#include "../Engine/InputManager.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Random.h"
#include "Scene_9.h"
#include "Scene_11.h"

void Scene_10::update(float deltaTime)
{
	Engine::InputManager &input = Engine::InputManager::getInstance();

	m_camera.update(deltaTime);

	glm::mat4 view = m_camera.getView();

	m_vao.bind();

	m_cubeShader.use();
	m_cubeMaterial.diffuse.bind(0);
	m_cubeMaterial.specular.bind(1);

	m_cubeShader.set("view", view);
	m_cubeShader.set("viewPosition", m_camera.position);
	m_cubeShader.set("light.position", m_camera.position);
	m_cubeShader.set("light.direction", m_camera.front);

	for(int i = 0; i < NUM_CUBES_SCENE_10; i++)
	{
		glm::mat4 cubeModel = m_cubes[i].genModelMatrix();
		m_cubeShader.set("model", cubeModel);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	m_cubeShader.unuse();

	m_vao.unbind();

	if(input.isKeyPressed(KEY_LEFT))
		Engine::SceneManager::getInstance().changeScene<Scene_9>();

	if(input.isKeyPressed(KEY_RIGHT))
		Engine::SceneManager::getInstance().changeScene<Scene_11>();

	if(input.isKeyPressed(KEY_R))
		m_camera.reset();
}

void Scene_10::onEnter()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	m_lightMaterial.ambient = { 0.05f, 0.05f, 0.05f };
	m_lightMaterial.diffuse = { 0.8f, 0.8f, 0.8f };
	m_lightMaterial.specular = { 1.0f, 1.0f, 1.0f };
	m_lightMaterial.constant = 1.0f;
	m_lightMaterial.linear = 0.09f;
	m_lightMaterial.quadratic = 0.032f;
	m_lightMaterial.innerCutOff = glm::cos(glm::radians(12.5f));
	m_lightMaterial.outerCutOff = glm::cos(glm::radians(17.5f));

	m_cubeMaterial.diffuse.load("resources/scene_10/textures/container2.png");
	m_cubeMaterial.specular.load("resources/scene_10/textures/container2_specular.png");
	m_cubeMaterial.shininess = 32.0f;

	glm::mat4 projection = Engine::ShaderProgram::genProjection(45.0f);

	m_cubeShader.loadShaders("resources/scene_10/shaders/cubeShader.vert", "resources/scene_10/shaders/cubeShader.frag");
	m_cubeShader.use();
	m_cubeShader.set("projection", projection);
	m_cubeShader.set("material.diffuse", 0);
	m_cubeShader.set("material.specular", 1);
	m_cubeShader.set("material.shininess", m_cubeMaterial.shininess);
	m_cubeShader.set("light.ambient", m_lightMaterial.ambient);
	m_cubeShader.set("light.diffuse", m_lightMaterial.diffuse);
	m_cubeShader.set("light.specular", m_lightMaterial.specular);
	m_cubeShader.set("light.constant", m_lightMaterial.constant);
	m_cubeShader.set("light.linear", m_lightMaterial.linear);
	m_cubeShader.set("light.quadratic", m_lightMaterial.quadratic);
	m_cubeShader.set("light.innerCutOff", m_lightMaterial.innerCutOff);
	m_cubeShader.set("light.outerCutOff", m_lightMaterial.outerCutOff);
	m_cubeShader.unuse();

	m_vao.init();
	m_vao.bind();
	m_vao.addAttribute(Shapes::cubeVertices, 3);
	m_vao.addAttribute(Shapes::cubeNormals, 3);
	m_vao.addAttribute(Shapes::cubeUvs, 2);
	m_vao.unbind();

	Engine::Random random;

	for(int i = 0; i < NUM_CUBES_SCENE_10; i++)
	{
		glm::vec3 pos = { random.nextDouble(-15, 0), random.nextDouble(-5, 5), random.nextDouble(-8, 8) };
		glm::vec3 rot = { random.nextDouble(0, 360), random.nextDouble(0, 360), random.nextDouble(0, 360) };

		float scale = random.nextDouble(0.2, 2);

		m_cubes[i].position = pos;
		m_cubes[i].rotation = rot;
		m_cubes[i].scale = { scale, scale, scale };
	}
}

void Scene_10::onExit()
{
	m_cubeShader.free();

	m_vao.clean();

	m_cubeMaterial.diffuse.free();
	m_cubeMaterial.specular.free();

	glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
}
