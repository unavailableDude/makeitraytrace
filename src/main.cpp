#include <iostream>
#include <vector>

#include "../include/SDL2/SDL.h"
#include "../include/glm/glm.hpp"
#include "../lib/imgui/imgui.h"
#include "../lib/imgui/backends/imgui_impl_sdl2.h"
#include "../lib/imgui/backends/imgui_impl_opengl3.h"

// MIRT
#include "../include/Vec4.hpp"
#include "../include/Ray.hpp"
#include "../include/Canvas.hpp"
#include "../include/Renderer.hpp"
#include "../include/Window.hpp"


const int SCRW = 640;
const int SCRH = 480;


int main(int argc, char* argv[]) {
	MIRT::Window window1("raytracer 0.05", SCRW, SCRH);

	MIRT::Renderer artist(600, 400);
	MIRT::Canvas canvas = artist.MakeArt();
	canvas.SaveToPPM("output.ppm", "P3");

	// the main loop
	SDL_Event event;
	bool running = true;
	while(running) {
		while(SDL_PollEvent(&event)) {
			ImGui_ImplSDL2_ProcessEvent(&event);
			if(event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE) {
				running = false;
			} else if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
				running = false;
			} else if(event.type == SDL_KEYDOWN) {
				switch(event.key.keysym.sym) {
				case SDLK_a: break;
				case SDLK_d: break;
				default: break;
				}
			}
		}
		window1.Update();
		SDL_Delay(16);
	}
	SDL_Quit();

	return 0;
}