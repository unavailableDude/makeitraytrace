#include "../include/Renderer.hpp"

#include <iostream>
#include <chrono>
#include <math.h>

// glm
#include <glm/ext/matrix_float4x4.hpp>// mat4
#include <glm/ext/matrix_transform.hpp>

#include "Sphere.hpp"
#include "Ray.hpp"
#include "RayHit.hpp"
#include "Vec4.hpp"


namespace MIRT {


Renderer::Renderer(uint16_t width = 480, uint16_t height = 320)
    : _width(width),
      _height(height),
      _aspectRatio(float(width) / float(height)) {}

Canvas Renderer::MakeArt() {
	// create sphere in the middle
	Sphere sphere1 = Sphere();
	glm::mat4 translation = glm::translate(glm::identity<glm::mat4>(), glm::vec3(-8.0f, -4.0f, 0.0f));
	glm::mat4 scaling = glm::scale(glm::identity<glm::mat4>(), glm::vec3(5.0f, 5.0f, 5.0f));
	sphere1.SetTransform(glm::transpose(translation * scaling));// convert it to row-major
	Material material1 = Material();
	material1.SetSurfaceColor(Color4(1.0f, 0.5f, 0.2f));
	sphere1.SetMaterial(material1);

	Sphere sphere2 = Sphere();
	translation = glm::translate(glm::identity<glm::mat4>(), glm::vec3(8.0f, 4.0f, 0.0f));
	scaling = glm::scale(glm::identity<glm::mat4>(), glm::vec3(5.0f, 5.0f, 5.0f));
	sphere2.SetTransform(glm::transpose(translation * scaling));
	Material material2 = Material();
	material2.SetSurfaceColor(Color4(0.2f, 0.5f, 1.0f));
	sphere2.SetMaterial(material2);

	Material materialBG = Material();
	materialBG.SetSurfaceColor(Color4(0.2f, 0.2f, 0.2f, 1.0f));

	auto renderStartTime = std::chrono::high_resolution_clock::now();

	// draw
	std::vector<Color4> pixels(_width * _height, Color4(1.0f, 0.0f, 1.0f, 1.0f));
	for(uint16_t y = 0; y < _height; ++y) {
		for(uint16_t x = 0; x < _width; ++x) {
			Color4 currColor(0.0f, 0.0f, 0.0f, 1.0f);
			Vec4 rayOrigin = Vec4(0.0f, 0.0f, -100.0f, 1.0f);

			float halfW = (_width / 2);
			float halfH = (_height / 2);

			Vec4 pixelPos = Vec4(float(x - halfW), float(y - halfH), -95.0f, 1.0f);
			pixelPos._x /= halfW;
			pixelPos._y /= halfH * _aspectRatio;
			Vec4 pixelDir = pixelPos - rayOrigin;

			Ray ray = Ray(MakePoint(rayOrigin), MakeDir(pixelDir));

			std::vector<RayHit> hits1 = sphere1.Intersect(ray);
			std::vector<RayHit> hits2 = sphere2.Intersect(ray);
			std::vector<RayHit> allHits;
			allHits.insert(allHits.end(), hits1.begin(), hits1.end());
			allHits.insert(allHits.end(), hits2.begin(), hits2.end());

			if(!allHits.empty()) {
				const RayHit& hit = FrontHit(allHits);
				Vec4 normal = hit.Normal();
				currColor = hit.Object()->GetMaterial().SurfaceColor();
				currColor = currColor * (1.0f - normal._x);
			} else
				currColor = materialBG.SurfaceColor();
			pixels[y * _width + x] = currColor;
		}
	}
	auto renderEndTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float, std::milli> renderDuration = renderEndTime - renderStartTime;
	std::cout << "Render time: " << renderDuration.count() << " ms" << std::endl;
	std::cout.flush();

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
	_aspectRatio = float(_width) / float(_height);
}

}// namespace MIRT