#include "Game.h"
#include "Scenes/SceneTests.h"
#include "Scenes/Scene_1.h"
#include "Engine/SceneManager.h"

void Game::startup()
{
	Engine::SceneManager::getInstance().changeScene<Scene_1>();
}

void Game::shutdown()
{
}
