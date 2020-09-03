#include "Game.h"
#include "SceneTests.h"
#include "Engine/SceneManager.h"

void Game::startup()
{
	Engine::SceneManager::getInstance().changeScene<SceneTests>();
}

void Game::shutdown()
{
}
