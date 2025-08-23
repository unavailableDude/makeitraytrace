#include <iostream>
#include <stdint.h>
#include <cassert>
#include <vector>
#include <cmath>

#include "../include/Color4.hpp"
#include "../include/Canvas.hpp"
#include "../include/Vec4.hpp"
using namespace MIRT;

// ANSI color codes
#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"


bool CanvasCheckDimensions(const Canvas& canvas,
                           uint16_t expectedWidth,
                           uint16_t expectedHeight,
                           const char* title = "",
                           bool print = true) {
	if(canvas.GetWidth() == expectedWidth && canvas.GetHeight() == expectedHeight) {
		if(print) std::cout << GREEN << "passed! " << title << RESET << std::endl;
		return true;
	} else {
		if(print)
			std::cerr << RED << "failed! " << title << " Expected dimensions: (" << expectedWidth << ", " << expectedHeight
			          << "), got: (" << canvas.GetWidth() << ", " << canvas.GetHeight() << ")" << RESET << std::endl;
		return false;
	}
}

bool CanvasCheckPixelColor(const Canvas& canvas,
                           uint16_t x,
                           uint16_t y,
                           const Color4& expectedColor,
                           const char* title = "",
                           bool print = true) {
	if(canvas.GetPixel(x, y) == expectedColor) {
		if(print) std::cout << GREEN << "passed! " << title << RESET << std::endl;
		return true;
	} else {
		if(print)
			std::cerr << RED << "failed! " << title << " Expected color: " << ToString(expectedColor)
			          << ", got: " << ToString(canvas.GetPixel(x, y)) << RESET << std::endl;
		return false;
	}
}

bool CanvasCheckWholeColor(const Canvas& canvas,
                           const Color4& expectedColor,
                           float eps,
                           const char* title = "",
                           bool print = true) {
	for(uint16_t y = 0; y < canvas.GetHeight(); ++y) {
		for(uint16_t x = 0; x < canvas.GetWidth(); ++x) {
			if(canvas.GetPixel(x, y) != expectedColor) {
				if(print)
					std::cerr << RED << "failed! " << title << " Expected color: " << ToString(expectedColor)
					          << ", got: " << ToString(canvas.GetPixel(x, y)) << RESET << std::endl;
				return false;
			}
		}
	}
	if(print) std::cout << GREEN << "passed! " << title << RESET << std::endl;
	return true;
}

bool CanvasIsMatchingCanvases(const Canvas& a, const Canvas& b, const char* title = "", bool print = true) {
	if(a.GetWidth() != b.GetWidth() || a.GetHeight() != b.GetHeight()) {
		if(print) std::cerr << RED << "failed! " << title << " Canvas dimensions do not match" << RESET << std::endl;
		return false;
	}
	bool didAllMatch = true;
	uint16_t mismatches = 0;
	for(uint16_t y = 0; y < a.GetHeight(); ++y) {
		for(uint16_t x = 0; x < a.GetWidth(); ++x) {
			if(a.GetPixel(x, y) != b.GetPixel(x, y)) {
				didAllMatch = false;
				++mismatches;
			}
		}
	}
	if(print) {
		if(didAllMatch) std::cout << GREEN << "passed! " << title << RESET << std::endl;
		else
			std::cerr << RED << "failed! " << title << " Mismatched pixels: " << mismatches << RESET << std::endl;
	}
	return true;
}

int main(int argc, char* argv[]) {
	float eps = Vec4::s_epsilon;
	Canvas canvas1(10, 20);
	CanvasCheckDimensions(canvas1, 10, 20, "Canvas creation with specified dimensions.");
	CanvasCheckWholeColor(canvas1, Color4(0, 0, 0, 1), eps, "Canvas initial color should be opaque black.");

	// setting dimensions after creation
	Canvas canvas2(400, 200);
	canvas2.SetDimensions(5, 2);
	CanvasCheckDimensions(canvas2, 5, 2, "changing canvas dimensions with SetDimensions.");

	// setting all pixels with SetPixels with an outside array
	std::vector<Color4> pixels(5 * 2, Color4(0.6f, 0.5f, 0.4f, 1.0f));
	canvas2.SetPixels(pixels);
	CanvasCheckWholeColor(canvas2, Color4(0.6f, 0.5f, 0.4f, 1.0f), eps, "setting all pixels with SetPixels.");

	// drawing a pixel
	canvas1.SetPixel(2, 3, Color4(1, 0, 0, 1));
	CanvasCheckPixelColor(canvas1, 2, 3, Color4(1, 0, 0, 1), "drawing a pixel results in that pixel getting colored.");

	// Save the canvas to a PPM file
	canvas1.SaveToPPM("../output.ppm", "P3");

	// load the canvas
	canvas2 = LoadPPM("../output.ppm");
	CanvasIsMatchingCanvases(canvas1, canvas2, "Loaded canvas should match saved canvas.");
}