#include <iostream>
#include <cmath>
#include <vector>

#include "Scene.hpp"
#include "Camera.hpp"
#include "Sphere.hpp"
#include "Vec4.hpp"


// ANSI color codes
#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"

using namespace MIRT;


// takes epsilon to account
bool CheckCamerasEqual(const Camera& cam1, const Camera& cam2, float eps = Vec4::s_epsilon) {
	return (cam1.Position() - cam2.Position()).Magnitude() < eps && (cam1.Forward() - cam2.Forward()).Magnitude() < eps &&
	       (cam1.Right() - cam2.Right()).Magnitude() < eps && (cam1.Up() - cam2.Up()).Magnitude() < eps;
}


int main(int argc, char* argv[]) {
	// check the defaults of scene when created
	MIRT::Scene scene;
	if(scene.GetSpheres().empty())
		std::cout << GREEN << "Passed: scene starts with empty list of objects" << RESET << std::endl;
	else
		std::cout << RED << "Failed: scene should start with empty list of objects" << RESET << std::endl;

	Camera defaultCam = Camera();
	if(CheckCamerasEqual(scene.GetCamera(), defaultCam))
		std::cout << GREEN << "Passed: scene starts with default camera" << RESET << std::endl;
	else
		std::cout << RED << "Failed: scene should start with default camera" << RESET << std::endl;
	return 0;
}