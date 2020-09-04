#include "Scene_9.h"
#include "../Shapes/CubeShape.h"
#include "../Engine/InputManager.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Random.h"
#include "Scene_8.h"

void Scene_9::update(float deltaTime)
{
	Engine::InputManager &input = Engine::InputManager::getInstance();

	m_camera.update(deltaTime);

	glm::mat4 view = m_camera.getView();

	m_vao.bind();

	m_lightShader.use();
	glm::mat4 lightModel = m_light.genModelMatrix();

	m_lightShader.set("view", view);
	m_lightShader.set("model", lightModel);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	m_lightShader.unuse();

	m_cubeShader.use();
	m_cubeMaterial.diffuse.bind(0);
	m_cubeMaterial.specular.bind(1);

	m_cubeShader.set("view", view);
	m_cubeShader.set("viewPosition", m_camera.position);
	m_cubeShader.set("light.position", m_light.position);

	for(int i = 0; i < NUM_CUBES_SCENE_9; i++)
	{
		glm::mat4 cubeModel = m_cubes[i].genModelMatrix();
		m_cubeShader.set("model", cubeModel);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	glDrawArrays(GL_TRIANGLES, 0, 36);

	m_cubeShader.unuse();

	m_vao.unbind();

	if(input.isKeyPressed(KEY_LEFT))
		Engine::SceneManager::getInstance().changeScene<Scene_8>();

	if(input.isKeyPressed(KEY_R))
		m_camera.reset();
}

void Scene_9::onEnter()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	m_light.scale = { 0.1f, 0.1f, 0.1f };

	m_lightMaterial.ambient = { 0.2f, 0.2, 0.2f };
	m_lightMaterial.diffuse = { 0.8f, 0.8f, 0.8f };
	m_lightMaterial.specular = { 1.0f, 1.0f, 1.0f };
	m_lightMaterial.constant = 1.0f;
	m_lightMaterial.linear = 0.09f;
	m_lightMaterial.quadratic = 0.032f;

	m_cubeMaterial.diffuse.load("resources/scene_8/textures/container2.png");
	m_cubeMaterial.specular.load("resources/scene_8/textures/container2_specular.png");
	m_cubeMaterial.shininess = 32.0f;

	glm::mat4 projection = Engine::ShaderProgram::genProjection(45.0f);

	m_lightShader.loadShaders("resources/scene_9/shaders/lightShader.vert", "resources/scene_9/shaders/lightShader.frag");
	m_lightShader.use();
	m_lightShader.set("projection", projection);
	m_lightShader.set("lightColor", m_lightMaterial.specular);
	m_lightShader.unuse();

	m_cubeShader.loadShaders("resources/scene_9/shaders/cubeShader.vert", "resources/scene_9/shaders/cubeShader.frag");
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
	m_cubeShader.unuse();

	m_vao.init();
	m_vao.bind();
	m_vao.addAttribute(Shapes::cubeVertices, 3);
	m_vao.addAttribute(Shapes::cubeNormals, 3);
	m_vao.addAttribute(Shapes::cubeUvs, 2);
	m_vao.unbind();

	Engine::Random random;

	for(int i = 0; i < NUM_CUBES_SCENE_9; i++)
	{
		glm::vec3 pos = { random.nextDouble(-5, 5), random.nextDouble(-2, 2), random.nextDouble(-4, 4) };
		glm::vec3 rot = { random.nextDouble(0, 360), random.nextDouble(0, 360), random.nextDouble(0, 360) };

		float scale = random.nextDouble(0.2, 2);

		m_cubes[i].position = pos;
		m_cubes[i].rotation = rot;
		m_cubes[i].scale = { scale, scale, scale };
	}
}

void Scene_9::onExit()
{
	m_lightShader.free();
	m_cubeShader.free();

	m_vao.clean();

	m_cubeMaterial.diffuse.free();
	m_cubeMaterial.specular.free();

	glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
}
