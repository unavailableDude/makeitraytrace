#include <iostream>
#include <vector>

#include "../include/SDL2/SDL.h"
#include "../include/glm/glm.hpp"

// MIRT
#include "../include/Vec4.hpp"
#include "../include/Ray.hpp"
#include "../include/Canvas.hpp"
#include "../include/Renderer.hpp"


const int SCRW = 640;
const int SCRH = 480;


int main(int argc, char* argv[]) {
	// initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "SDL could not be initialized! SDL_Error: " << SDL_GetError() << std::endl;
		return -1;
	}
	SDL_Window* window1 =
	    SDL_CreateWindow("raytracer 0.04", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCRW, SCRH, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer1 = SDL_CreateRenderer(window1, -1, SDL_RENDERER_ACCELERATED);
	if(window1 == NULL) {
		std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		return -1;
	}
	if(renderer1 == NULL) {
		std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		return -1;
	}

	// random garbage you will see, unless with black you clear the scree...n
	SDL_SetRenderDrawColor(renderer1, 0, 0, 0, 255);
	SDL_RenderClear(renderer1);

	MIRT::Renderer artist(600, 400);
	MIRT::Canvas canvas = artist.MakeArt();
	canvas.SaveToPPM("../outputPPM/output.ppm", "P3");

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

		SDL_SetRenderDrawColor(renderer1, 255, 255, 255, 255);
		SDL_RenderPresent(renderer1);
		SDL_Delay(16);
	}
	SDL_Quit();

	return 0;
}