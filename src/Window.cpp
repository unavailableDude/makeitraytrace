#include "../include/Window.hpp"


#include <iostream>

#include "../lib/imgui/imgui.h"
#include "../lib/imgui/backends/imgui_impl_sdl2.h"
#include "../lib/imgui/backends/imgui_impl_opengl3.h"

#include "OpenGLLayer.hpp"


namespace MIRT {


// Define the static member variable
bool Window::s_isSDLInitialized = false;


Window::Window() : _renderer(nullptr) {}
Window::Window(const char* title, int w, int h) : _renderer(nullptr) {
	// init order: SDL -> OGL attr -> Window -> OGL context -> ImGUI
	InitializeSDL();


	_SDLWindow = SDL_CreateWindow(title,
	                              SDL_WINDOWPOS_UNDEFINED,
	                              SDL_WINDOWPOS_UNDEFINED,
	                              w,
	                              h,
	                              SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if(_SDLWindow == NULL) {
		std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		throw std::runtime_error("Window: Window could not be created!");
	}

	_glContext = SDL_GL_CreateContext(_SDLWindow);
	if(!_glContext) {
		std::cerr << "Window: OpenGL context could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		throw std::runtime_error("Window: OpenGL context could not be created!");
	}

	// Set SDL OpenGL attributes before creating window, this has to be done before creating the gl context
	OpenGLLayer::InitOGL();
	// Initialize ImGui after OpenGL context is created
	InitializeImGUI();

	_width = w;
	_height = h;
}

Window::~Window() {
	// Cleanup ImGui, multiple checks in case there is "residue" that isn't cleaned up
	if(ImGui::GetCurrentContext()) ImGui_ImplOpenGL3_Shutdown();
	if(ImGui::GetCurrentContext()) ImGui_ImplSDL2_Shutdown();
	if(ImGui::GetCurrentContext()) ImGui::DestroyContext();

	// Cleanup SDL
	SDL_GL_DeleteContext(_glContext);
	// SDL_DestroyRenderer(_SDLRenderer);
	SDL_DestroyWindow(_SDLWindow);
}

void Window::SetRenderer(Renderer* renderer) { _renderer = renderer; }
void Window::SetTextureToShow(uint32_t textureID) { _textureToShow = textureID; }

void Window::Update() { DrawGUI(); }

void Window::DrawGUI() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	// Create an invisible fullscreen window to act as docking space
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->WorkPos);
	ImGui::SetNextWindowSize(viewport->WorkSize);
	ImGui::SetNextWindowViewport(viewport->ID);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;
	window_flags |=
	    ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	window_flags |= ImGuiWindowFlags_NoBackground;

	ImGui::Begin("DockSpaceWindow", nullptr, window_flags);
	ImGui::PopStyleVar(3);

	// Create the dockspace
	ImGuiID dockspace_id = ImGui::GetID("MainDockSpace");
	ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);
	ImGui::End();

	// Debug frame
	ImGui::Begin("Debug Info");
	ImGui::Text("Render Time: xx ms");
	ImGui::End();

	// Viewport frame
	ImGui::Begin("Viewport");
	ImGui::Image((ImTextureID)_renderer->GetFrameBufferID(), ImVec2(_width, _height));
	ImGui::End();

	ImGui::Render();
	glViewport(0, 0, _width, _height);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	SDL_GL_SwapWindow(_SDLWindow);
}

bool Window::InitializeSDL() {
	if(s_isSDLInitialized) return true;
	// initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "Window: SDL could not be initialized! SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}

	s_isSDLInitialized = true;
	return true;
}

bool Window::InitializeImGUI() {
	// Initialize ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;// Enable Docking

	// Setup ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer backends
	ImGui_ImplSDL2_InitForOpenGL(_SDLWindow, _glContext);
	ImGui_ImplOpenGL3_Init("#version 130");

	return true;
}

}// namespace MIRT