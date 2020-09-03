#ifndef __GAME_H__
#define __GAME_H__

#include "Engine/Core.h"

class Game : public Engine::Core
{
public:
	virtual void startup() override final;

	virtual void shutdown() override final;
private:
};

#endif // !__GAME_H__
