#include "OpenGLLayer.hpp"

#include "CommonMacros.hpp"
#include "SDL.h"

#include <iostream>


namespace MIRT {

bool OpenGLLayer::_OGLInitialized = false;
OpenGLLayer::OpenGLLayer() { _OGLInitialized = false; }

bool OpenGLLayer::InitOGL() {
	if(_OGLInitialized) return true;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	if(!gladLoadGLLoader(SDL_GL_GetProcAddress)) {// load opengl functions, segfault if ignored!
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	// openGL info
	std::cout << "OpenGL Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	_OGLInitialized = true;

	return true;
}

bool OpenGLLayer::LoadImageToBuffer(Canvas& canvas, GLuint& textureID) {
	GLuint imageTexture;
	glGenTextures(1, &imageTexture);
	glBindTexture(GL_TEXTURE_2D, imageTexture);

	// Setup filtering parameters for display
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	uint32_t* pixelArray = canvas.GetPixelArray();
	// Upload pixels into texture
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
	glTexImage2D(GL_TEXTURE_2D,
	             0,
	             GL_RGBA,
	             canvas.GetWidth(),
	             canvas.GetHeight(),
	             0,
	             GL_RGBA,
	             GL_UNSIGNED_BYTE,
	             (GLvoid*)(pixelArray));

	textureID = imageTexture;
	return true;
}

bool OpenGLLayer::CreateTexture(uint16_t width, uint16_t height, GLuint& textureID) {
	GLuint id;
	bool ret = false;
	GLCALL(glGenTextures(1, &id);)
	GLCALL(glBindTexture(GL_TEXTURE_2D, id);)
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);)
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);)
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);)
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);)
	GLCALL(glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA32F, width, height);)
	textureID = id;
	return (ret = true);
}

}// namespace MIRT