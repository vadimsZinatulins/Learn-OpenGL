#include "Scene_11.h"
#include "../Shapes/CubeShape.h"
#include "../Engine/InputManager.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Random.h"
#include "Scene_10.h"

void Scene_11::update(float deltaTime)
{
	Engine::InputManager &input = Engine::InputManager::getInstance();

	m_camera.update(deltaTime);

	glm::mat4 view = m_camera.getView();

	static float elapsedTime = 0.0f;
	static float moveSpeed = 32.0f;
	elapsedTime += deltaTime * moveSpeed;

	const glm::vec3 moveAxsis[NUM_POINT_LIGHTS_SCENE_11] = {
		{ 1.0f, 0.0f, 0.0f },
		{ 1.0f, 1.0f, 1.0f },
		{ 1.0f, 1.0f, 0.0f },
		{ 0.0f, 1.0f, 1.0f }
	};

	const float radiuses[NUM_POINT_LIGHTS_SCENE_11] = {
		5.0f,
		8.5f,
		10.0f,
		4.5f
	};

	glm::vec3 lightPos[NUM_POINT_LIGHTS_SCENE_11] = {
		glm::vec3(glm::cos(glm::radians(elapsedTime)), glm::sin(glm::radians(elapsedTime)), glm::cos(glm::radians(elapsedTime))) * radiuses[0] * moveAxsis[0] + m_pointLights[0].position,
		glm::vec3(glm::cos(glm::radians(elapsedTime)), glm::sin(glm::radians(elapsedTime)), glm::cos(glm::radians(elapsedTime))) * radiuses[1] * moveAxsis[1] + m_pointLights[1].position,
		glm::vec3(glm::cos(glm::radians(elapsedTime)), glm::sin(glm::radians(elapsedTime)), glm::cos(glm::radians(elapsedTime))) * radiuses[2] * moveAxsis[2] + m_pointLights[2].position,
		glm::vec3(glm::cos(glm::radians(elapsedTime)), glm::sin(glm::radians(elapsedTime)), glm::cos(glm::radians(elapsedTime))) * radiuses[3] * moveAxsis[3] + m_pointLights[3].position
	};

	m_vao.bind();

	m_lightShader.use();
	m_lightShader.set("view", view);
	for(int i = 0; i < NUM_POINT_LIGHTS_SCENE_11; i++)
	{
		glm::mat4 lightModel = glm::translate(glm::mat4(1), lightPos[i]);

		glm::vec3 lightColor = m_pointLightMaterials[i].material.specular;

		m_lightShader.set("model", lightModel);
		m_lightShader.set("lightColor", lightColor);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	m_lightShader.unuse();

	m_cubeShader.use();
	m_cubeMaterial.diffuse.bind(0);
	m_cubeMaterial.specular.bind(1);

	m_cubeShader.set("view", view);


	m_cubeShader.set("viewPosition", m_camera.position);

	// Setup Point lights
	for(int i = 0; i < NUM_POINT_LIGHTS_SCENE_11; i++)
		m_cubeShader.set((std::string("pointLights[") + std::to_string(i) + std::string("].position")).c_str(), lightPos[i]);

	m_cubeShader.set("spotLight.position", m_camera.position);
	m_cubeShader.set("spotLight.direction", m_camera.front);

	for(int i = 0; i < NUM_CUBES_SCENE_11; i++)
	{
		glm::mat4 cubeModel = m_cubes[i].genModelMatrix();
		m_cubeShader.set("model", cubeModel);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	m_cubeShader.unuse();

	m_vao.unbind();

	if(input.isKeyPressed(KEY_LEFT))
		Engine::SceneManager::getInstance().changeScene<Scene_10>();

	if(input.isKeyPressed(KEY_R))
		m_camera.reset();
}

void Scene_11::onEnter()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	m_dirLightMaterial.direction = { -0.3f, -1.0f, 0.2f };
	m_dirLightMaterial.material.ambient = { 0.01f, 0.01f, 0.01f };
	m_dirLightMaterial.material.diffuse = { 0.8f, 0.8f, 0.8f };
	m_dirLightMaterial.material.specular = { 1.0f, 1.0f, 1.0f };

	Engine::Random random;

	for(int i = 0; i < NUM_POINT_LIGHTS_SCENE_11; i++)
	{
		m_pointLightMaterials[i].constant = 1.0f;
		m_pointLightMaterials[i].linear = 0.09f;
		m_pointLightMaterials[i].quadratic = 0.032f;

		m_pointLightMaterials[i].material.ambient = { 0.01f, 0.01f, 0.01f };
		m_pointLightMaterials[i].material.diffuse = { 0.8f, 0.8f, 0.8f };
		m_pointLightMaterials[i].material.specular = { 1.0f, 1.0f, 1.0f };

		m_pointLights[i].position = { random.nextDouble(-15, 15), random.nextDouble(-15, 15), random.nextDouble(-15, 15) };
	}

	m_spotLightMaterial.material.ambient = { 0.01f, 0.01f, 0.01f };
	m_spotLightMaterial.material.diffuse = { 0.8f, 0.8f, 0.8f };
	m_spotLightMaterial.material.specular = { 1.0f, 1.0f, 1.0f };
	m_spotLightMaterial.constant = 1.0f;
	m_spotLightMaterial.linear = 0.09f;
	m_spotLightMaterial.quadratic = 0.032f;
	m_spotLightMaterial.innerCutOff = glm::cos(glm::radians(12.5f));
	m_spotLightMaterial.outerCutOff = glm::cos(glm::radians(17.5f));

	m_cubeMaterial.diffuse.load("resources/scene_11/textures/container2.png");
	m_cubeMaterial.specular.load("resources/scene_11/textures/container2_specular.png");
	m_cubeMaterial.shininess = 32.0f;

	glm::mat4 projection = Engine::ShaderProgram::genProjection(45.0f);

	m_cubeShader.loadShaders("resources/scene_11/shaders/cubeShader.vert", "resources/scene_11/shaders/cubeShader.frag");
	m_cubeShader.use();
	m_cubeShader.set("projection", projection);
	m_cubeShader.set("material.diffuse", 0);
	m_cubeShader.set("material.specular", 1);
	m_cubeShader.set("material.shininess", m_cubeMaterial.shininess);
	// Setup Directional Light
	m_cubeShader.set("dirLight.direction", m_dirLightMaterial.direction);
	m_cubeShader.set("dirLight.ambient", m_dirLightMaterial.material.ambient);
	m_cubeShader.set("dirLight.diffuse", m_dirLightMaterial.material.diffuse);
	m_cubeShader.set("dirLight.specular", m_dirLightMaterial.material.specular);
	// Setup Point lights
	for(int i = 0; i < NUM_POINT_LIGHTS_SCENE_11; i++)
	{
		m_cubeShader.set((std::string("pointLights[") + std::to_string(i) + std::string("].position")).c_str(), m_pointLights[i].position);

		m_cubeShader.set((std::string("pointLights[") + std::to_string(i) + std::string("].constant")).c_str(), m_pointLightMaterials[i].constant);
		m_cubeShader.set((std::string("pointLights[") + std::to_string(i) + std::string("].linear")).c_str(), m_pointLightMaterials[i].linear);
		m_cubeShader.set((std::string("pointLights[") + std::to_string(i) + std::string("].quadratic")).c_str(), m_pointLightMaterials[i].quadratic);

		m_cubeShader.set((std::string("pointLights[") + std::to_string(i) + std::string("].ambient")).c_str(), m_pointLightMaterials[i].material.ambient);
		m_cubeShader.set((std::string("pointLights[") + std::to_string(i) + std::string("].diffuse")).c_str(), m_pointLightMaterials[i].material.diffuse);
		m_cubeShader.set((std::string("pointLights[") + std::to_string(i) + std::string("].specular")).c_str(), m_pointLightMaterials[i].material.specular);
	}
	// Setup Spot Light
	m_cubeShader.set("spotLight.position", m_camera.position);
	m_cubeShader.set("spotLight.direction", m_camera.front);
	m_cubeShader.set("spotLight.constant", m_spotLightMaterial.constant);
	m_cubeShader.set("spotLight.linear", m_spotLightMaterial.linear);
	m_cubeShader.set("spotLight.quadratic", m_spotLightMaterial.quadratic);
	m_cubeShader.set("spotLight.innerCutOff", m_spotLightMaterial.innerCutOff);
	m_cubeShader.set("spotLight.outerCutOff", m_spotLightMaterial.outerCutOff);
	m_cubeShader.set("spotLight.ambient", m_spotLightMaterial.material.ambient);
	m_cubeShader.set("spotLight.diffuse", m_spotLightMaterial.material.diffuse);
	m_cubeShader.set("spotLight.specular", m_spotLightMaterial.material.specular);
	m_cubeShader.unuse();

	m_lightShader.loadShaders("resources/scene_11/shaders/lightShader.vert", "resources/scene_11/shaders/lightShader.frag");
	m_lightShader.use();
	m_lightShader.set("projection", projection);
	m_lightShader.unuse();

	m_vao.init();
	m_vao.bind();
	m_vao.addAttribute(Shapes::cubeVertices, 3);
	m_vao.addAttribute(Shapes::cubeNormals, 3);
	m_vao.addAttribute(Shapes::cubeUvs, 2);
	m_vao.unbind();

	for(int i = 0; i < NUM_CUBES_SCENE_11; i++)
	{
		glm::vec3 pos = { random.nextDouble(-15, 15), random.nextDouble(-15, 15), random.nextDouble(-15, 15) };
		glm::vec3 rot = { random.nextDouble(0, 360), random.nextDouble(0, 360), random.nextDouble(0, 360) };

		float scale = random.nextDouble(0.5, 2.5);

		m_cubes[i].position = pos;
		m_cubes[i].rotation = rot;
		m_cubes[i].scale = { scale, scale, scale };
	}
}

void Scene_11::onExit()
{
	m_cubeShader.free();
	m_lightShader.free();

	m_vao.clean();

	m_cubeMaterial.diffuse.free();
	m_cubeMaterial.specular.free();

	glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
}
