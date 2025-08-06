#include <iostream>
#include <vector>

#include "../include/SDL2/SDL.h"

// RTCE
#include "../include/Vec4.hpp"
#include "../include/Ray.hpp"


const int SCRW = 640;
const int SCRH = 480;


using RTCE::Vec4;


void TickProjectile(Vec4& position, Vec4& velocity, Vec4& influenceAcceleration, float deltaTime) {
	position = position + velocity * deltaTime;
	velocity = velocity + (influenceAcceleration * deltaTime);
}


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

	Vec4 projectile1Position = RTCE::MakePoint(Vec4(0.0f, 0.0f, 0.0f));
	Vec4 projectile1Velocity = RTCE::MakeDir(Vec4(50.0f, 50.0f, 0.0f));
	Vec4 influenceAcceleration = RTCE::MakeDir(Vec4(-4.0f, -9.81f, 0.0f));// wind effects x, gravity effects y

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

		TickProjectile(projectile1Position, projectile1Velocity, influenceAcceleration, 0.0166f);

		// draw array
		SDL_SetRenderDrawColor(renderer1, 255, 255, 255, 255);

		SDL_RenderDrawPoint(renderer1, projectile1Position._x, SCRH - projectile1Position._y);

		SDL_RenderPresent(renderer1);
		SDL_Delay(16);
		// SDL_SetRenderDrawColor(renderer1, 0, 0, 0, 255);
		// SDL_RenderClear(renderer1);
	}
	SDL_Quit();

	return 0;
}