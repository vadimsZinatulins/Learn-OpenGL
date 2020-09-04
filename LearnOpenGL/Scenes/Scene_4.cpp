#include "Scene_4.h"
#include "../Shapes/CubeShape.h"
#include "../Engine/InputManager.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Random.h"
#include "Scene_3.h"
#include "Scene_5.h"

void Scene_4::update(float deltaTime)
{
	Engine::InputManager &input = Engine::InputManager::getInstance();

	m_camera.update(deltaTime);

	glm::mat4 view = m_camera.getView();

	m_shader.use();
	m_vao.bind();

	m_shader.set("view", view);

	m_texture1.bind(0);
	m_shader.set("tex1", 0);

	m_texture2.bind(1);
	m_shader.set("tex2", 1);

	for(int i = 0; i < NUM_CUBES_SCENE_4; i++)
	{
		glm::mat4 quadModel = m_cubes[i].genModelMatrix();
		m_shader.set("model", quadModel);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	m_vao.unbind();
	m_shader.unuse();

	if(input.isKeyPressed(KEY_LEFT))
		Engine::SceneManager::getInstance().changeScene<Scene_3>();

	if(input.isKeyPressed(KEY_RIGHT))
		Engine::SceneManager::getInstance().changeScene<Scene_5>();
}

void Scene_4::onEnter()
{
	glm::mat4 projection = Engine::ShaderProgram::genProjection(45.0f);

	m_shader.loadShaders("resources/scene_4/shaders/shader.vert", "resources/scene_4/shaders/shader.frag");
	m_shader.use();
	m_shader.set("projection", projection);
	m_shader.unuse();

	m_texture1.load("resources/scene_3/textures/container.jpg");
	m_texture2.load("resources/scene_3/textures/awesomeface.png");

	m_vao.init();
	m_vao.bind();
	m_vao.addAttribute(Shapes::cubeVertices, 3);
	m_vao.addAttribute(Shapes::cubeUvs, 2);
	m_vao.unbind();

	Engine::Random random;

	for(int i = 0; i < NUM_CUBES_SCENE_4; i++)
	{
		glm::vec3 pos = { random.nextDouble(-5, 5), random.nextDouble(-2, 2), random.nextDouble(-4, 4) };
		glm::vec3 rot = { random.nextDouble(0, 360), random.nextDouble(0, 360), random.nextDouble(0, 360) };

		float scale = random.nextDouble(0.2, 2);

		m_cubes[i].position = pos;
		m_cubes[i].rotation = rot;
		m_cubes[i].scale = { scale, scale, scale };
	}
}

void Scene_4::onExit()
{
	m_shader.free();

	m_vao.clean();

	m_texture1.free();
	m_texture2.free();
}
