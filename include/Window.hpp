#pragma once


#include "../include/SDL2/SDL.h"


namespace MIRT {

class Window {
public:
	Window();
	Window(const char* title, int width, int height);
	~Window();

	void Update();

private:
	bool InitializeSDL();
	bool InitializeImGUI();
	void DrawGUI();

	SDL_Window* _SDLWindow;
	SDL_Renderer* _SDLRenderer;
	SDL_GLContext _glContext;
	static bool s_isSDLInitialized;
	uint16_t _width;
	uint16_t _height;
};

}// namespace MIRT