#include "Scene_1.h"
#include "../Shapes/TriangleShape.h"
#include "../Engine/InputManager.h"
#include "../Engine/SceneManager.h"
#include "Scene_2.h"

void Scene_1::update(float deltaTime)
{
	Engine::InputManager &input = Engine::InputManager::getInstance();

	m_shader.use();
	m_vao.bind();

	glDrawArrays(GL_TRIANGLES, 0, 3);

	m_vao.unbind();
	m_shader.unuse();

	if(input.isKeyPressed(KEY_RIGHT))
		Engine::SceneManager::getInstance().changeScene<Scene_2>();
}

void Scene_1::onEnter()
{
	m_shader.loadShaders("resources/scene_1/shaders/shader.vert", "resources/scene_1/shaders/shader.frag");

	m_vao.init();
	m_vao.bind();
	m_vao.addAttribute(Shapes::triangleVertices, 3);
	m_vao.unbind();
}

void Scene_1::onExit()
{
	m_shader.free();

	m_vao.clean();
}
