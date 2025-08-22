#pragma once


#include <cstdint>
#include <vector>

#include "glad/glad.h"

#include "ShaderProgram.hpp"


namespace MIRT {


class Renderer {
public:
	Renderer(uint16_t width, uint16_t height);

	void MakeArt();
	bool PreparePipeline();

	uint16_t GetWidth() const;
	uint16_t GetHeight() const;
	unsigned int GetFrameBufferID() const;

	void SetImageDimensions(uint16_t width, uint16_t height);

private:
	uint16_t _width;
	uint16_t _height;
	float _aspectRatio;

	unsigned int _fbo;
	unsigned int _colorTexture;
	unsigned int _vao;
	unsigned int _vbo;// to hold 4 vertices for the 2 triangles that will span the whole viewport
	ShaderProgram _shaderProgram;
};

}// namespace MIRT