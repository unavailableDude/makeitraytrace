#pragma once


#include "SDL.h"
#include "glad/glad.h"

#include "Canvas.hpp"
#include "Color4.hpp"


namespace MIRT {


class OpenGLLayer {
public:
	OpenGLLayer();

	// Initialize OpenGL
	static bool InitOGL();

	// loads the image data to an openGL texture buffer, and returns a GLuint texture ID representing the texture's ID
	static bool LoadImageToBuffer(Canvas& canvas, GLuint& textureID);
	static bool CreateTexture(uint16_t width, uint16_t height, GLuint& textureID);

private:
	static bool _OGLInitialized;
};

}// namespace MIRT