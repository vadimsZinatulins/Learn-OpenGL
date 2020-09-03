#include "Scene_2.h"
#include "../Shapes/TriangleShape.h"
#include "../Engine/InputManager.h"
#include "../Engine/SceneManager.h"
#include "Scene_1.h"
#include "Scene_3.h"

void Scene_2::update(float deltaTime)
{
	Engine::InputManager &input = Engine::InputManager::getInstance();

	m_shader.use();
	m_vao.bind();

	glDrawArrays(GL_TRIANGLES, 0, 3);

	m_vao.unbind();
	m_shader.unuse();

	if(input.isKeyPressed(KEY_LEFT))
		Engine::SceneManager::getInstance().changeScene<Scene_1>();

	if(input.isKeyPressed(KEY_RIGHT))
		Engine::SceneManager::getInstance().changeScene<Scene_3>();
}

void Scene_2::onEnter()
{
	std::vector<float> triangleColor = { 
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};
	m_shader.loadShaders("resources/scene_2/shaders/shader.vert", "resources/scene_2/shaders/shader.frag");

	m_vao.init();
	m_vao.bind();
	m_vao.addAttribute(Shapes::triangleVertices, 3);
	m_vao.addAttribute(triangleColor, 3);
	m_vao.unbind();
}

void Scene_2::onExit()
{
	m_shader.free();

	m_vao.clean();
}
