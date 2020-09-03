#ifndef __INPUT_MANAGER_H__
#define __INPUT_MANAGER_H__

#include <unordered_map>

#include "Keys.h"

using Keys = std::unordered_map<Key, bool>;

struct MouseCoords
{
	float x{ 0.0f };
	float y{ 0.0f };
};

class InputManager
{
public:
	static InputManager &getInstance();

	void keyPressed(Key key);
	void keyReleased(Key key);

	void setMouseCoords(MouseCoords coords);
	void setMouseCoordsRel(MouseCoords coords);

	void update();

	bool isKeyPressed(Key key);
	bool isKeyDown(Key key);
	bool isKeyReleased(Key key);

	MouseCoords getMouseCoords();
	MouseCoords getMouseCoordsRel();
private:
	InputManager();
	~InputManager();

	bool wasKeyDown(Key key);

	static InputManager m_instance;

	Keys m_currKeys;
	Keys m_oldKeys;

	MouseCoords m_mouseCoords;
	MouseCoords m_mouseCoordsRel;
};

#endif // !__INPUT_MANAGER_H__
