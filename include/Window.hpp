#pragma once


#include "../include/SDL2/SDL.h"
#include "Renderer.hpp"


namespace MIRT {

class Window {
public:
	Window();
	Window(const char* title, int width, int height);
	~Window();

	void SetRenderer(Renderer* renderer);
	void SetTextureToShow(uint32_t textureID);

	void Update();

private:
	bool InitializeSDL();
	bool InitializeImGUI();
	void DrawGUI();

	SDL_Window* _SDLWindow;
	SDL_Renderer* _SDLRenderer;
	SDL_GLContext _glContext;
	Renderer* _renderer;// MIRT renderer
	static bool s_isSDLInitialized;
	uint16_t _width;
	uint16_t _height;
	uint32_t _textureToShow;
};

}// namespace MIRT