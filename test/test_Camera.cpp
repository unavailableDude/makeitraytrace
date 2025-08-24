#include "Camera.hpp"

#include <iostream>
#include <cmath>


using namespace MIRT;

// ANSI color codes
#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"


// returns true for equal, takes s_epsilon into account
bool AssertEqual(const Vec4& a, float x, float y, float z, float w, float eps, const char* title = "") {
	if((fabs(a._x - x) < eps) && (fabs(a._y - y) < eps) && (fabs(a._z - z) < eps) && (fabs(a._w - w) < eps)) {
		std::cout << GREEN << "passed! " << title << RESET << std::endl;
		return true;
	}
	std::cerr << RED << "failed! " << title << " Expected: (" << x << ", " << y << ", " << z << ", " << w << "), Got: ("
	          << a._x << ", " << a._y << ", " << a._z << ", " << a._w << ")" << RESET << std::endl;
	return false;
}


int main(int argc, char** argv) {
	Camera camera1;
	AssertEqual(camera1.Position(), 0.0f, 0.0f, 0.0f, 1.0f, Vec4::s_epsilon, "Default camera position is (0, 0, 0, 1)");
	AssertEqual(camera1.Forward(), 0.0f, 0.0f, -1.0f, 0.0f, Vec4::s_epsilon, "Default camera forward is (0, 0, -1, 0)");
	AssertEqual(camera1.Right(), 1.0f, 0.0f, 0.0f, 0.0f, Vec4::s_epsilon, "Default camera right is (1, 0, 0, 0)");
	AssertEqual(camera1.Up(), 0.0f, 1.0f, 0.0f, 0.0f, Vec4::s_epsilon, "Default camera up is (0, 1, 0, 0)");

	camera1.SetPosition(Vec4(1.0f, 2.0f, 3.0f, 1.0f));
	AssertEqual(camera1.Position(),
	            1.0f,
	            2.0f,
	            3.0f,
	            1.0f,
	            Vec4::s_epsilon,
	            "Camera.SetPosition() sets position to given values");
	camera1.SetForward(Vec4(0.0f, 0.0f, -1.0f, 0.0f));
	AssertEqual(camera1.Forward(),
	            0.0f,
	            0.0f,
	            -1.0f,
	            0.0f,
	            Vec4::s_epsilon,
	            "Camera.SetForward() sets forward to given values");
	camera1.SetRight(Vec4(1.0f, 0.0f, 0.0f, 0.0f));
	AssertEqual(camera1.Right(), 1.0f, 0.0f, 0.0f, 0.0f, Vec4::s_epsilon, "Camera.SetRight() sets right to given values");
	camera1.SetUp(Vec4(0.0f, 1.0f, 0.0f, 0.0f));
	AssertEqual(camera1.Up(), 0.0f, 1.0f, 0.0f, 0.0f, Vec4::s_epsilon, "Camera.SetUp() sets up to given values");

	return 0;
}