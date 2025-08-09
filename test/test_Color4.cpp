#include <iostream>
#include <cassert>
#include <cmath>

#include "../include/Color4.hpp"
#include "../include/Vec4.hpp"
using namespace MIRT;

// ANSI color codes
#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"


// returns true for equal, takes s_epsilon into account
bool AssertEqual(const Color4& c, float r, float g, float b, float a, float eps, const char* title = "") {
	if((fabs(c.r() - r) < eps) && (fabs(c.g() - g) < eps) && (fabs(c.b() - b) < eps) && (fabs(c.a() - a) < eps)) {
		std::cout << GREEN << "passed! " << title << RESET << std::endl;
		return true;
	}
	std::cerr << RED << "failed! " << title << " Expected: (" << r << ", " << g << ", " << b << ", " << a << "), Got: ("
	          << c.r() << ", " << c.g() << ", " << c.b() << ", " << c.a() << ")" << RESET << std::endl;
	return false;
}

bool AssertFloatEqual(float a, float b, float eps, const char* title = "") {
	if(fabs(a - b) < eps) {
		std::cout << GREEN << "passed! " << title << RESET << std::endl;
		return true;
	}
	std::cerr << RED << "failed! " << title << " Expected: " << b << ", Got: " << a << RESET << std::endl;
	return false;
}

int main(int argc, char* argv[]) {
	float eps = Vec4::s_epsilon;

	// test if color with specified values is created correctly
	Color4 color1 = Color4(0.5f, 0.25f, 0.75f, 1.0f);
	Color4 color2 = Color4(0.5f, 0.25f, 0.75f);
	Color4 color3 = Color4(0.5f, 0.25f);
	Color4 color4 = Color4(0.5f);
	Color4 color5 = Color4();
	AssertEqual(color1,
	            0.5f,
	            0.25f,
	            0.75f,
	            1.0f,
	            eps,
	            "Color4 init with (0.5, 0.25, 0.75, 1.0), returns Color(0.5, 0.25, 0.75, 1.0)");
	AssertEqual(color2, 0.5f, 0.25f, 0.75f, 0.0f, eps, "Color4 init with (0.5, 0.25, 0.75) returns Color(0.5, 0.25, 0.75, 0)");
	AssertEqual(color3, 0.5f, 0.25f, 0.0f, 0.0f, eps, "Color4 init with (0.5, 0.25) returns Color(0.5, 0.25, 0, 0)");
	AssertEqual(color4, 0.5, 0.0, 0.0, 0.0, eps, "Color4 init with (0.5) returns Color(0.5, 0, 0, 0)");
	AssertEqual(color5, 0.0, 0.0, 0.0, 0.0, eps, "Color4 init with no arguments returns Color(0, 0, 0, 0)");

	// test for the operations + - * /
	Color4 colorA = Color4(0.9f, 0.6f, 0.75f, 0.4f);
	Color4 colorB = Color4(0.7f, 0.1f, 0.25f, 0.8f);

	AssertEqual(colorA + colorB, 1.6f, 0.7f, 1.0f, 1.2f, eps, "Color4 addition");
	AssertEqual(colorA - colorB, 0.2f, 0.5f, 0.5f, -0.4f, eps, "Color4 subtraction");
	AssertEqual(colorA * colorB, 0.63f, 0.06f, 0.1875f, 0.32f, eps, "Color4 hadamard product");
	AssertEqual(colorA * 2.0f, 1.8f, 1.2f, 1.5f, 0.8f, eps, "Color4 scalar multiplication");
	AssertEqual(colorA / colorB, 1.285714f, 6.0f, 3.0f, 0.5f, eps, "Color4 hadamard division");
	AssertEqual(colorA / 2.0f, 0.45f, 0.3f, 0.375f, 0.2f, eps, "Color4 scalar division");

	return 0;
}