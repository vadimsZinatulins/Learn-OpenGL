#include "SceneManager.h"

namespace Engine
{

SceneManager SceneManager::m_instance;

SceneManager &SceneManager::getInstance()
{
	return m_instance;
}

void SceneManager::update(float deltaTime)
{
	if(m_nextScene)
	{
		m_currScene->onExit();
		m_currScene.swap(m_nextScene);
		m_currScene->onEnter();

		m_nextScene.release();
	}

	m_currScene->update(deltaTime);
}

bool SceneManager::isRunning() const
{
	// If scene exists, then get its 'isRunning' value
	if(m_currScene)
		return m_currScene->isRunning();

	return false;
}

void SceneManager::quit()
{
	m_currScene->quit();
}

void SceneManager::startup()
{
	// Initialize Scene only if it exists
	if(m_currScene)
		m_currScene->onEnter();
}

void SceneManager::shutdown()
{
	if(m_currScene)
		m_currScene->onExit();
}

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

}
