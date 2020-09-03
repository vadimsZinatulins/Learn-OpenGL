#include "Scene_3.h"
#include "../Shapes/QuadShape.h"
#include "../Engine/InputManager.h"
#include "../Engine/SceneManager.h"
#include "Scene_2.h"

void Scene_3::update(float deltaTime)
{
	Engine::InputManager &input = Engine::InputManager::getInstance();

	m_shader.use();
	m_vao.bind();

	m_texture1.bind(0);
	m_shader.set("tex1", 0);

	m_texture2.bind(1);
	m_shader.set("tex2", 1);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	m_vao.unbind();
	m_shader.unuse();

	if(input.isKeyPressed(KEY_LEFT))
		Engine::SceneManager::getInstance().changeScene<Scene_2>();
}

void Scene_3::onEnter()
{
	m_shader.loadShaders("resources/scene_3/shaders/shader.vert", "resources/scene_3/shaders/shader.frag");

	m_texture1.load("resources/scene_3/textures/container.jpg");
	m_texture2.load("resources/scene_3/textures/awesomeface.png");

	m_vao.init();
	m_vao.bind();
	m_vao.addAttribute(Shapes::quadVertices, 3);
	m_vao.addAttribute(Shapes::quadUvs, 2);
	m_vao.unbind();
}

void Scene_3::onExit()
{
	m_shader.free();

	m_vao.clean();

	m_texture1.free();
	m_texture2.free();
}
