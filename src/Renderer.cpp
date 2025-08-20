#include "../include/Renderer.hpp"

#include <iostream>

// glm
#include <glm/ext/matrix_float4x4.hpp>// mat4
#include <glm/ext/matrix_transform.hpp>

#include "Sphere.hpp"
#include "Ray.hpp"
#include "RayHit.hpp"
#include "Vec4.hpp"


namespace MIRT {


Renderer::Renderer(uint16_t width = 480, uint16_t height = 320) : _width(width), _height(height) {}

Canvas Renderer::MakeArt() {
	// create sphere in the middle
	Sphere sphere1 = Sphere();
	glm::mat4 translation = glm::translate(glm::identity<glm::mat4>(), glm::vec3(float(_width / 2), float(_height / 2), 0.0f));
	glm::mat4 scaling = glm::scale(glm::identity<glm::mat4>(), glm::vec3(100.0f, 100.0f, 100.0f));
	sphere1.SetTransform(glm::transpose(translation * scaling));// convert it to row-major

	// draw
	std::vector<Color4> pixels(_width * _height, Color4(1.0f, 0.0f, 1.0f, 1.0f));
	float dist = 100.0f;
	for(uint16_t y = 0; y < _height; ++y) {
		for(uint16_t x = 0; x < _width; ++x) {
			Color4 currColor(0.0f, 0.0f, 0.0f, 1.0f);
			Ray ray = Ray(MakePoint(Vec4(float(x), float(y), -100.1f)), MakeDir(Vec4(0.0f, 0.0f, 1.0f)));
			std::vector<RayHit> hits = sphere1.Intersect(ray);
			if(!hits.empty()) {
				const RayHit& hit = FrontHit(hits);
				std::cout << hit.T() << std::endl;
				currColor = Color4((hit.T() / dist), (hit.T() / dist), (hit.T() / dist), 1.0f);
			}
			pixels[y * _width + x] = currColor;
		}
	}

	// create canvas and return it
	Canvas canvas(_width, _height);
	canvas.SetPixels(pixels);
	return canvas;
}

uint16_t Renderer::GetWidth() const { return _width; }
uint16_t Renderer::GetHeight() const { return _height; }

void Renderer::SetImageDimensions(uint16_t width, uint16_t height) {
	_width = width;
	_height = height;
}

}// namespace MIRT