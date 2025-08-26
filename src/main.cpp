#include <iostream>
#include <vector>
#include <cstdint>

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
#include "OpenGLLayer.hpp"
#include "Scene.hpp"
#include "Camera.hpp"
#include "Sphere.hpp"


const int SCRW = 1920;
const int SCRH = 1080;


int main(int argc, char* argv[]) {
	MIRT::Window window1("raytracer 0.10", SCRW, SCRH);

	MIRT::Scene scene = MIRT::Scene();
	MIRT::Camera cam = MIRT::Camera(MIRT::Vec4(0.0f, 0.0f, 6.0f, 1.0f),  // pos
	                                MIRT::Vec4(0.0f, 1.0f, 0.0f, 0.0f),  // up
	                                MIRT::Vec4(1.0f, 0.0f, 0.0f, 0.0f),  // right
	                                MIRT::Vec4(0.0f, 0.0f, -1.0f, 0.0f));// forward

	scene.SetCamera(cam);
	scene.GenerateRandomSpheres(14);

	MIRT::Sphere sphere1 = MIRT::Sphere();
	sphere1.SetTransform(MIRT::Vec4(0.0f, 0.0f, 0.0f, 1.0f), MIRT::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
	MIRT::Material mat1 = MIRT::Material();
	mat1.SetSurfaceColor(MIRT::Color4(0.2f, 1.0f, 0.2f, 1.0f));
	mat1.SetShininess(200.0f);
	sphere1.SetMaterial(mat1);
	sphere1.SetId(14);
	MIRT::Sphere groundSphere = MIRT::Sphere();
	groundSphere.SetTransform(MIRT::Vec4(0.0f, 2.8f, 0.0f, 1.0f), MIRT::Vec4(40.0f, 1.0f, 40.0f, 1.0f));
	groundSphere.SetId(15);
	MIRT::Material groundMat = MIRT::Material();
	groundMat.SetSurfaceColor(MIRT::Color4(0.8f, 0.2f, 0.2f, 1.0f));
	groundMat.SetShininess(0.0f);
	groundMat.SetAmbient(0.0f);
	groundMat.SetDiffuse(1.0f);
	groundMat.SetSpecular(0.0f);
	groundSphere.SetMaterial(groundMat);

	scene.AddSphere(sphere1);
	scene.AddSphere(groundSphere);

	MIRT::Renderer artist(1600, 1000);
	artist.SetCurrentScene(scene);
	artist.PreparePipeline();

	window1.SetRenderer(&artist);

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
				case SDLK_p: artist.Save("screenshot.ppm"); break;
				default: break;
				}
			}
		}
		artist.MakeArt();
		window1.Update();
		SDL_Delay(16);
	}
	SDL_Quit();

	return 0;
}