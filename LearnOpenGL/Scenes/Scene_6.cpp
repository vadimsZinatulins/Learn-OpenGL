#include "Scene_6.h"
#include "../Shapes/CubeShape.h"
#include "../Engine/InputManager.h"
#include "../Engine/SceneManager.h"
#include "Scene_5.h"
#include "Scene_7.h"

void Scene_6::update(float deltaTime)
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
	glm::mat4 cubeModel = m_cube.genModelMatrix();

	m_cubeShader.set("view", view);
	m_cubeShader.set("model", cubeModel);
	m_cubeShader.set("lightPosition", m_light.position);
	m_cubeShader.set("viewPosition", m_camera.position);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	m_cubeShader.unuse();
	
	m_vao.unbind();

	if(input.isKeyPressed(KEY_LEFT))
		Engine::SceneManager::getInstance().changeScene<Scene_5>();

	if(input.isKeyPressed(KEY_RIGHT))
		Engine::SceneManager::getInstance().changeScene<Scene_7>();

	if(input.isKeyPressed(KEY_R))
		m_camera.reset();
}

void Scene_6::onEnter()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	m_light.position = { -0.8f, 1.0f, -2.0f };
	m_lightColor = { 1.0f, 1.0f, 1.0f };

	m_cubeColor = { 1.0f, 0.5f, 0.31f };

	glm::mat4 projection = Engine::ShaderProgram::genProjection(45.0f);

	m_lightShader.loadShaders("resources/scene_6/shaders/lightShader.vert", "resources/scene_6/shaders/lightShader.frag");
	m_lightShader.use();
	m_lightShader.set("projection", projection);
	m_lightShader.set("lightColor", m_lightColor);
	m_lightShader.unuse();

	m_cubeShader.loadShaders("resources/scene_6/shaders/cubeShader.vert", "resources/scene_6/shaders/cubeShader.frag");
	m_cubeShader.use();
	m_cubeShader.set("projection", projection);
	m_cubeShader.set("cubeColor", m_cubeColor);
	m_cubeShader.set("lightColor", m_lightColor);
	m_cubeShader.unuse();

	m_vao.init();
	m_vao.bind();
	m_vao.addAttribute(Shapes::cubeVertices, 3);
	m_vao.addAttribute(Shapes::cubeNormals, 3);
	m_vao.unbind();
}

void Scene_6::onExit()
{
	m_lightShader.free();
	m_cubeShader.free();

	m_vao.clean();

	glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
}
