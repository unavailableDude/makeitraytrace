#include "../include/Canvas.hpp"

#include <iostream>
#include <fstream>


namespace MIRT {


uint16_t Canvas::GetWidth() const { return _width; }

uint16_t Canvas::GetHeight() const { return _height; }

void Canvas::SetDimensions(uint16_t width, uint16_t height) {
	_width = width;
	_height = height;
	_pixels.resize(width * height, Color4(0.0f, 0.0f, 0.0f, 1.0f));
}

void Canvas::SetPixels(const std::vector<Color4>& pixels) { _pixels = pixels; }

void Canvas::SetPixel(uint16_t x, uint16_t y, const Color4& color) {
	if(x < _width && y < _height) {
		_pixels[y * _width + x] = color;
	}
}

Color4 Canvas::GetPixel(uint16_t x, uint16_t y) const {
	if(x < _width && y < _height) {
		return _pixels[y * _width + x];
	}
	return Color4();// Return a default color if out of bounds
}

void Canvas::SaveToPPM(const std::string& filename, const std::string& magicNumber) const {
	// std::cout << "SaveToPPM not finished" << std::endl;
	// return;
	std::ofstream file(filename);
	if(!file) throw std::runtime_error("SaveToPPM(): file " + filename + " could not be opened");

	// Write the PPM header
	file << magicNumber << std::endl;
	file << _width << " " << _height << std::endl;
	file << "255" << std::endl;

	// Write the pixel data
	for(uint16_t y = 0; y < _height; ++y) {
		for(uint16_t x = 0; x < _width; ++x) {
			const Color4& pixel = GetPixel(x, y);
			// casting to uint16_t to avoid weird values that produce wrong colors when loaded by LoadPPM
			file << static_cast<uint16_t>(pixel.r() * 255) << " " << static_cast<uint16_t>(pixel.g() * 255) << " "
			     << static_cast<uint16_t>(pixel.b() * 255) << " ";
		}
		file << "\n";
	}

	file.close();
}

Canvas& LoadPPM(const std::string& filename) {
	std::ifstream file(filename);
	if(!file) throw std::runtime_error("LoadPPM(): file " + filename + " could not be opened");

	// read magic number
	std::string magicNumber;
	file >> magicNumber;
	if(magicNumber != "P3") throw std::runtime_error("LoadPPM(): magic numbers other than P3 are not supported... yet");

	// read width and height
	uint16_t width, height;
	file >> width >> height;// ppm should enforce this to be positive

	// read max color value
	uint16_t maxColorValue;
	file >> maxColorValue;
	if(maxColorValue != 255) {
		throw std::runtime_error("LoadPPM(): only max color value of 255 is supported");
	}

	// create canvas
	Canvas* canvas = new Canvas(width, height);
	for(uint16_t y = 0; y < height; ++y) {
		for(uint16_t x = 0; x < width; ++x) {
			uint16_t r, g, b;
			file >> r >> g >> b;
			canvas->SetPixel(x, y, Color4(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f));
		}
	}

	file.close();
	return *canvas;
}

}// namespace MIRT