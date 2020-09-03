#ifndef __CORE_H__
#define __CORE_H__

#include <sdl/SDL.h>
#include <string>

namespace Engine
{

class Core
{
public:
	Core();
	virtual ~Core();

	void run();
protected:
	virtual void startup();
	virtual void shutdown();

	void setTitle(std::string title);
	void setResolution(int width, int height);
	void setFullScreen(bool fullScreenFlag);
private:
	void init();
	void loop();
	void close();

	std::string m_title;

	int m_width;
	int m_height;

	bool m_isFullScreen;

	SDL_Window *m_window;
	SDL_GLContext m_context;
};

}


#endif // !__CORE_H__
