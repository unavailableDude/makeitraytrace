#include <iostream>
#include <vector>

#include "../include/SDL2/SDL.h"

// RTCE
#include "../include/Vec4.hpp"
#include "../include/Ray.hpp"


const int SCRW = 640;
const int SCRH = 480;


int main(int argc, char* argv[]) {
	// initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "SDL could not be initialized! SDL_Error: " << SDL_GetError() << std::endl;
		return -1;
	}
	SDL_Window* window1 =
	    SDL_CreateWindow("raytracer 0.0003", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCRW, SCRH, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer1 = SDL_CreateRenderer(window1, -1, SDL_RENDERER_ACCELERATED);
	if(window1 == NULL) {
		std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		return -1;
	}
	if(renderer1 == NULL) {
		std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		return -1;
	}

	RTCE::Vec4 CameraPos = RTCE::MakePoint(RTCE::Vec4(0.0f, 0.0f, 0.0f));
	RTCE::Vec4 CameraDir = RTCE::MakeDir(RTCE::Vec4(0.0f, 0.0f, -1.0f));
	float CameraFov = 90.0f;// Field of view in degrees
	float aspectRatio = static_cast<float>(SCRW) / static_cast<float>(SCRH);
	std::vector<RTCE::Ray> rays(SCRW * SCRH, RTCE::Ray());
	std::vector<RTCE::Vec4> frameBuffer(SCRW * SCRH, RTCE::Vec4(0.0f, 0.0f, 0.0f, 0.0f));// rgba

	SDL_Event event;
	bool running = true;
	while(running) {
		while(SDL_PollEvent(&event)) {
			if(event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE) {
				running = false;
				SDL_DestroyWindow(window1);
				return 0;
			} else if(event.key.keysym.sym == SDLK_ESCAPE) {
				running = false;
				SDL_DestroyWindow(window1);
				return 0;
			} else if(event.type == SDL_KEYDOWN) {
				switch(event.key.keysym.sym) {
				case SDLK_a: break;
				case SDLK_d: break;
				default: break;
				}
			}
		}

		// draw array
		SDL_SetRenderDrawColor(renderer1, 255, 255, 255, 255);

		SDL_RenderPresent(renderer1);
		SDL_Delay(16);
		SDL_SetRenderDrawColor(renderer1, 0, 0, 0, 255);
		SDL_RenderClear(renderer1);
	}

	SDL_Quit();

	return 0;
}