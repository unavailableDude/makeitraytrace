#pragma once


#include <cstdint>
#include <chrono>
#include <vector>

#include "glad/glad.h"

#include "ShaderProgram.hpp"
#include "ComputeShaderProgram.hpp"
#include "Sphere.hpp"
#include "Camera.hpp"


namespace MIRT {


class Renderer {
public:
	Renderer(uint16_t width, uint16_t height);

	void MakeArt();
	bool PreparePipeline();

	uint16_t GetWidth() const;
	uint16_t GetHeight() const;
	unsigned int GetFrameBufferID() const;
	std::chrono::duration<float, std::milli> GetLastFrameDeltaTime() const;

	void SetImageDimensions(uint16_t width, uint16_t height);

private:
	uint16_t _width;
	uint16_t _height;
	float _aspectRatio;

	unsigned int _fbo;
	unsigned int _colorTexture;
	unsigned int _vao;                         // cool comments bro
	unsigned int _vbo;                         // to hold 4 vertices for the 2 triangles that will span the whole viewport
	                                           //
	unsigned int _SphereSSBO;                  // to hold buffer for spheres
	std::vector<Sphere> _spheres;              // the spheres in the scene
	uint16_t _numSpheres;                      // number of spheres
	unsigned int _cameraSSBO;                  // to hold buffer for camera
	Camera _sceneCamera;                       // the camera for the scene
	                                           //
	ShaderProgram _shaderProgram;              // for the vert/fragment shader
	ComputeShaderProgram _computeShaderProgram;// for the compute shader
	std::chrono::duration<float, std::milli> _lastFrameDeltaTime;
};

}// namespace MIRT