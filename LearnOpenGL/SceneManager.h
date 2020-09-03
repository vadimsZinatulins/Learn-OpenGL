#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

#include <memory>

#include "IScene.h"

class SceneManager
{
public:
	static SceneManager &getInstance();

	template <typename T>
	void changeScene();

	void update(float deltaTime);

	bool isRunning() const;
	void quit();

	void startup();
	void shutdown();
private:
	SceneManager();
	~SceneManager();

	static SceneManager m_instance;

	std::unique_ptr<IScene>	m_currScene;
	std::unique_ptr<IScene>	m_nextScene;
};

template<typename T>
inline void SceneManager::changeScene()
{
	if(m_currScene)
	{
		if(m_nextScene)
			m_nextScene.release();

		m_nextScene = std::make_unique<T>();
	}
	else
		m_currScene = std::make_unique<T>();
}

#endif // !__SCENE_MANAGER_H__
