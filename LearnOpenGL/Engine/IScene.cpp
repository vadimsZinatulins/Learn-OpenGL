#include "IScene.h"

namespace Engine
{

IScene::IScene() :
    m_isRunning(true)
{
}

IScene::~IScene()
{
}

void IScene::onEnter()
{
}

void IScene::onExit()
{
}

bool IScene::isRunning() const
{
    return m_isRunning;
}

void IScene::quit()
{
    m_isRunning = false;
}

}
