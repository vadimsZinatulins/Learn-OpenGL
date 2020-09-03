#ifndef __SCENE_TESTS_H__
#define __SCENE_TESTS_H__

#include "Engine/IScene.h"

class SceneTests : public Engine::IScene
{
public:
	virtual void update(float deltaTime) override final;

	virtual void onEnter() override final;
	virtual void onExit() override final;
};

#endif // !__SCENE_TESTS_H__
