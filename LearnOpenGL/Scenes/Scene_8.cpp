#include "Scene_8.h"
#include "../Shapes/CubeShape.h"
#include "../Engine/InputManager.h"
#include "../Engine/SceneManager.h"
#include "Scene_7.h"

void Scene_8::update(float deltaTime)
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

	glm::mat4 cubeModel = m_cube.genModelMatrix();

	m_cubeShader.set("model", cubeModel);
	m_cubeShader.set("view", view);
	m_cubeShader.set("viewPosition", m_camera.position);
	m_cubeShader.set("light.position", m_light.position);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	m_cubeShader.unuse();

	m_vao.unbind();

	if(input.isKeyPressed(KEY_LEFT))
		Engine::SceneManager::getInstance().changeScene<Scene_7>();

	if(input.isKeyPressed(KEY_R))
		m_camera.reset();
}

void Scene_8::onEnter()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	m_light.position = { -0.8f, 1.0f, -2.0f };
	m_lightMaterial.ambient = { 0.2f, 0.2f, 0.2f };
	m_lightMaterial.diffuse = { 0.5f, 0.5f, 0.5f };
	m_lightMaterial.specular = { 1.0f, 1.0f, 1.0f };

	m_cubeMaterial.diffuse.load("resources/scene_8/textures/container2.png");
	m_cubeMaterial.specular.load("resources/scene_8/textures/container2_specular.png");
	m_cubeMaterial.shininess = 32.0f;

	glm::mat4 projection = Engine::ShaderProgram::genProjection(45.0f);

	m_lightShader.loadShaders("resources/scene_8/shaders/lightShader.vert", "resources/scene_8/shaders/lightShader.frag");
	m_lightShader.use();
	m_lightShader.set("projection", projection);
	m_lightShader.set("lightColor", m_lightMaterial.specular);
	m_lightShader.unuse();

	m_cubeShader.loadShaders("resources/scene_8/shaders/cubeShader.vert", "resources/scene_8/shaders/cubeShader.frag");
	m_cubeShader.use();
	m_cubeShader.set("projection", projection);
	m_cubeShader.set("material.diffuse", 0);
	m_cubeShader.set("material.specular", 1);
	m_cubeShader.set("material.shininess", m_cubeMaterial.shininess);
	m_cubeShader.set("light.ambient", m_lightMaterial.ambient);
	m_cubeShader.set("light.diffuse", m_lightMaterial.diffuse);
	m_cubeShader.set("light.specular", m_lightMaterial.specular);
	m_cubeShader.unuse();

	m_vao.init();
	m_vao.bind();
	m_vao.addAttribute(Shapes::cubeVertices, 3);
	m_vao.addAttribute(Shapes::cubeNormals, 3);
	m_vao.addAttribute(Shapes::cubeUvs, 2);
	m_vao.unbind();
}

void Scene_8::onExit()
{
	m_lightShader.free();
	m_cubeShader.free();

	m_vao.clean();

	m_cubeMaterial.diffuse.free();
	m_cubeMaterial.specular.free();

	glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
}
