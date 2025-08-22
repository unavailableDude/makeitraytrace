#pragma once

#include <stdint.h>
#include <vector>
#include <string>

#include "Color4.hpp"


namespace MIRT {


class Canvas {
public:
	Canvas(uint16_t w = 720, uint16_t h = 480) : _width(w), _height(h), _pixels(w * h, Color4(0.0f, 0.0f, 0.0f, 1.0f)) {}

	uint16_t GetWidth() const;
	uint16_t GetHeight() const;

	void SetDimensions(uint16_t width, uint16_t height);
	void SetPixels(const std::vector<Color4>& pixels);
	void SetPixel(uint16_t x, uint16_t y, const Color4& color);
	Color4 GetPixel(uint16_t x, uint16_t y) const;

	// saves the canvas to ppm file, the saved colors are scaled to [0, 255]
	void SaveToPPM(const std::string& filename, const std::string& magicNumber, bool flipY = false) const;

private:
	uint16_t _width;
	uint16_t _height;

	std::vector<Color4> _pixels;
};

// creates a canvas from a ppm file
Canvas& LoadPPM(const std::string& filename);

}// namespace MIRT