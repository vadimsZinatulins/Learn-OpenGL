#include "Core.h"
#include "InputManager.h"
#include "SceneManager.h"

#include <glad/glad.h>
#include <iostream>

const Uint32 FPS = 60;
const Uint32 MIN_TICKS_PER_FRAME = 1000 / FPS;

Core::Core() :
	m_title("Open GL"),
	m_width(1024),
	m_height(768),
	m_isFullScreen(false),
	m_window(nullptr),
	m_context(nullptr)
{
}

Core::~Core()
{
}

void Core::run()
{
	init();
	loop();
	close();
}

void Core::startup()
{
}

void Core::shutdown()
{
}

void Core::setTitle(std::string title)
{
	m_title = title;

	if(m_window)
		SDL_SetWindowTitle(m_window, m_title.c_str());
}

void Core::setResolution(int width, int height)
{
	m_width = width;
	m_height = height;

	if(m_window)
	{
		SDL_SetWindowSize(m_window, m_width, m_height);
		glViewport(0, 0, m_width, m_height);
	}
}

void Core::setFullScreen(bool fullScreenFlag)
{
	m_isFullScreen = fullScreenFlag;

	if(m_window)
	{
		SDL_SetWindowFullscreen(m_window, m_isFullScreen ? SDL_WINDOW_FULLSCREEN : 0);
	}
}

void Core::init()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	//SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GL_SetSwapInterval(1);

	m_window = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | (m_isFullScreen ? SDL_WINDOW_FULLSCREEN : 0));
	m_context = SDL_GL_CreateContext(m_window);

	gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);

	glViewport(0, 0, m_width, m_height);
	glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	SDL_SetRelativeMouseMode(SDL_TRUE);
}

void Core::loop()
{
	SDL_Event e;

	InputManager &input = InputManager::getInstance();
	SceneManager &scene = SceneManager::getInstance();

	startup();

	Uint32 currentFrameTicks = SDL_GetTicks();
	Uint32 lastFrameTicks = SDL_GetTicks();

	scene.startup();

	while(scene.isRunning())
	{
		currentFrameTicks = SDL_GetTicks();
		float deltaTime = (float)(currentFrameTicks - lastFrameTicks) / 1000.0f;
		lastFrameTicks = currentFrameTicks;

		input.update();

		while(SDL_PollEvent(&e))
		{
			switch(e.type)
			{
			case SDL_QUIT:
				scene.quit();
				break;
			case SDL_KEYDOWN:
				input.keyPressed(e.key.keysym.scancode);
				break;
			case SDL_KEYUP:
				input.keyReleased(e.key.keysym.scancode);
				break;
			case SDL_MOUSEMOTION:
				input.setMouseCoords({ (float)e.motion.x, (float)e.motion.y });
				input.setMouseCoordsRel({ (float)e.motion.xrel, (float)e.motion.yrel });
				break;
			}
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		scene.update(deltaTime);

		SDL_GL_SwapWindow(m_window);

		Uint32 frameTicks = SDL_GetTicks();
		if(frameTicks < MIN_TICKS_PER_FRAME)
			SDL_Delay(MIN_TICKS_PER_FRAME - frameTicks);
	}

	scene.shutdown();

	shutdown();
}

void Core::close()
{
	if(m_context)
	{
		SDL_GL_DeleteContext(m_context);
		m_context = nullptr;
	}

	if(m_window)
	{
		SDL_DestroyWindow(m_window);
		m_window = nullptr;
	}

	SDL_Quit();
}
