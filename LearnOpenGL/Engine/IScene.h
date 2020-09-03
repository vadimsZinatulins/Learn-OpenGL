#ifndef __ISCENE_H__
#define __ISCENE_H__

namespace Engine
{

class IScene
{
public:
	IScene();
	virtual ~IScene();

	virtual void update(float deltaTime) = 0;

	virtual void onEnter();
	virtual void onExit();

	bool isRunning() const;
	void quit();
private:
	bool m_isRunning;
};

}

#endif // !__ISCENE_H__
