#pragma once
#include "glad/glad.h"
#include <iostream>


#define ASSERT(x)                                                                                                             \
	if(!(x)) __debugbreak();

#define GLCALL(x)                                                                                                             \
	GLCLEARERROR();                                                                                                           \
	x;                                                                                                                        \
	ASSERT(GLLOGCALL(#x, __FILE__, __LINE__))

static void GLCLEARERROR() { while(glGetError() != GL_NO_ERROR); }
static bool GLLOGCALL(const char* function, const char* file, int line) {
	while(GLenum error = glGetError()) {
		std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ":" << line << std::endl;

		return false;
	}
	return true;
}