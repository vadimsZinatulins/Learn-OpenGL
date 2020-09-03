#include "InputManager.h"

InputManager InputManager::m_instance;

InputManager &InputManager::getInstance()
{
	return m_instance;
}

void InputManager::keyPressed(Key key)
{
	m_currKeys[key] = true;
}

void InputManager::keyReleased(Key key)
{
	m_currKeys[key] = false;
}

void InputManager::setMouseCoords(MouseCoords coords)
{
	m_mouseCoords = coords;
}

void InputManager::setMouseCoordsRel(MouseCoords coords)
{
	m_mouseCoordsRel = coords;
}

void InputManager::update()
{
	for(auto &key : m_currKeys)
		m_oldKeys[key.first] = key.second;

	m_mouseCoordsRel = { 0.0f, 0.0f };
}

bool InputManager::isKeyPressed(Key key)
{
	return isKeyDown(key) && !wasKeyDown(key);
}

bool InputManager::isKeyDown(Key key)
{
	auto ptr = m_currKeys.find(key);
	if(ptr == m_currKeys.end())
		return false;

	return ptr->second;
}

bool InputManager::isKeyReleased(Key key)
{
	return !isKeyDown(key) && wasKeyDown(key);
}

MouseCoords InputManager::getMouseCoords()
{
	return m_mouseCoords;
}

MouseCoords InputManager::getMouseCoordsRel()
{
	return m_mouseCoordsRel;
}

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

bool InputManager::wasKeyDown(Key key)
{
	auto ptr = m_oldKeys.find(key);
	if(ptr == m_oldKeys.end())
		return false;

	return ptr->second;
}
