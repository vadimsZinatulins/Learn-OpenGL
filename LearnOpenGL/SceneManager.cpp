#include "SceneManager.h"

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
	return m_currScene->isRunning();
}

void SceneManager::quit()
{
	m_currScene->quit();
}

void SceneManager::startup()
{
	m_currScene->onEnter();
}

void SceneManager::shutdown()
{
	m_currScene->onExit();
}

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}
