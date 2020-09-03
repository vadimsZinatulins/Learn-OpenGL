#include "SceneTests.h"
#include "Engine/InputManager.h"

#include <map>

void SceneTests::update(float deltaTime)
{
	Engine::InputManager &input = Engine::InputManager::getInstance();

	Engine::MouseCoords mouseCoordsRel = input.getMouseCoordsRel();
	m_camera.yaw += mouseCoordsRel.x * deltaTime * m_camera.rotationSpeed;
	m_camera.pitch -= mouseCoordsRel.y * deltaTime * m_camera.rotationSpeed;

	if(m_camera.pitch > 89.0f)
		m_camera.pitch = 89.0f;
	else if(m_camera.pitch < -89.0f)
		m_camera.pitch = -89.0f;

	glm::vec3 direction;
	direction.x = glm::cos(glm::radians(m_camera.yaw)) * glm::cos(glm::radians(m_camera.pitch));
	direction.y = glm::sin(glm::radians(m_camera.pitch));
	direction.z = glm::sin(glm::radians(m_camera.yaw)) * glm::cos(glm::radians(m_camera.pitch));
	m_camera.front = glm::normalize(direction);

	float speed = m_camera.moveSpeed * deltaTime;
	m_camera.position += input.isKeyDown(KEY_W) * speed * m_camera.front + input.isKeyDown(KEY_S) * speed * m_camera.front * -1.0f;
	m_camera.position += input.isKeyDown(KEY_D) * speed * glm::normalize(glm::cross(m_camera.front, m_camera.up)) + input.isKeyDown(KEY_A) * speed * glm::normalize(glm::cross(m_camera.up, m_camera.front));

	glm::mat4 view = m_camera.getView();

	renderCubes(view);
	renderPlanes(view, m_camera.position);
}

void SceneTests::onEnter()
{
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1024.0f / 768.0f, 0.1f, 100.0f);

	std::vector<float> cubeVertices = {
			-0.5f,  0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f, -0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f, -0.5f
	};

	std::vector<float> cubeUVs = {
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f
	};

	std::vector<float> planeVertices = {
		-0.5f,  0.5f,  0.0f,
		-0.5f, -0.5f,  0.0f,
		 0.5f, -0.5f,  0.0f,
		 0.5f, -0.5f,  0.0f,
		 0.5f,  0.5f,  0.0f,
		-0.5f,  0.5f,  0.0f
	};

	std::vector<float> planeUVs = {
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f
	};

	m_simpleShader.loadShaders("resources/shaders/simpleShader.vert", "resources/shaders/simpleShader.frag");
	m_simpleShader.use();
	m_simpleShader.set("projection", projection);
	m_simpleShader.unuse();

	m_marbleTexture.load("resources/textures/marble.jpg");

	m_metalTexture.load("resources/textures/metal.jpg");

	m_grassTexture.load("resources/textures/grass.png");

	m_windowTexture.load("resources/textures/window.png");

	m_cubeVertexBuffer.init();
	m_cubeVertexBuffer.bind();
	m_cubeVertexBuffer.addAttribute(cubeVertices, 3);
	m_cubeVertexBuffer.addAttribute(cubeUVs, 2);
	m_cubeVertexBuffer.unbind();

	m_planeVertexBuffer.init();
	m_planeVertexBuffer.bind();
	m_planeVertexBuffer.addAttribute(planeVertices, 3);
	m_planeVertexBuffer.addAttribute(planeUVs, 2);
	m_planeVertexBuffer.unbind();

	m_cube1.position = { 1.2f, 0.5f, 0.0f };
	m_cube2.position = { -1.2f, 0.5f, 0.0f };
	m_ground.scale = { 15.0f, 0.5f, 15.0f };
	m_ground.position = { 0.0f, -0.25f, 0.0f };
	m_grass1.position = { 1.2f, 0.5f, 0.51f };
	m_grass2.position = { -1.2f, 0.51f, 0.51f };
	m_grass3.position = { 1.2f + 0.51f, 0.5f, 0.0f };
	m_grass3.rotation = { 0.0f, 90.0f, 0.0f };
	m_window1.position = { 0.0f, 0.5f, 0.0f };
	m_window2.position = { 0.5f, 0.5f, -0.65f };
	m_window3.position = { 0.0f, 0.5f, 1.0f };
	m_window4.position = { -0.65f, 0.5f, 0.65f };
}

void SceneTests::onExit()
{
	m_marbleTexture.free();
	m_metalTexture.free();
	m_grassTexture.free();
	m_windowTexture.free();

	m_simpleShader.free();

	m_cubeVertexBuffer.clean();
}

void SceneTests::renderCubes(glm::mat4 &view)
{
	m_simpleShader.use();
	m_cubeVertexBuffer.bind();

	m_simpleShader.set("view", view);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_metalTexture);

	glm::mat4 groundModel = m_ground.genModelMatrix();
	m_simpleShader.set("model", groundModel);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindTexture(GL_TEXTURE_2D, m_marbleTexture);

	glm::mat4 cube1Model1 = m_cube1.genModelMatrix();
	m_simpleShader.set("model", cube1Model1);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glm::mat4 cube2Model1 = m_cube2.genModelMatrix();
	m_simpleShader.set("model", cube2Model1);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	m_cubeVertexBuffer.unbind();
	m_simpleShader.unuse();
}

void SceneTests::renderPlanes(glm::mat4 &view, glm::vec3 &camPosition)
{
	std::map<float, Pair> distancePairs;

	distancePairs[glm::length(camPosition - m_grass1.position)] = { m_grassTexture, m_grass1 };
	distancePairs[glm::length(camPosition - m_grass2.position)] = { m_grassTexture, m_grass2 };
	distancePairs[glm::length(camPosition - m_grass3.position)] = { m_grassTexture, m_grass3 };
	distancePairs[glm::length(camPosition - m_window1.position)] = { m_windowTexture, m_window1 };
	distancePairs[glm::length(camPosition - m_window2.position)] = { m_windowTexture, m_window2 };
	distancePairs[glm::length(camPosition - m_window3.position)] = { m_windowTexture, m_window3 };
	distancePairs[glm::length(camPosition - m_window4.position)] = { m_windowTexture, m_window4 };

	m_simpleShader.use();
	m_planeVertexBuffer.bind();

	for(auto pair = distancePairs.rbegin(); pair != distancePairs.rend(); pair++)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, pair->second.texture);

		glm::mat4 modelMatrix = pair->second.transform.genModelMatrix();
		m_simpleShader.set("model", modelMatrix);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	m_planeVertexBuffer.unbind();
	m_simpleShader.unuse();
}
