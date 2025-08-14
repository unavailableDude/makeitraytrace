#include <iostream>
#include <cmath>

#include "../include/Ray.hpp"
using namespace MIRT;


// ANSI color codes
#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"


bool CheckRayOrigin(const Ray& ray, float x, float y, float z, float eps = Vec4::s_epsilon) {
	return (fabs(ray.origin()._x - x) < eps) && (fabs(ray.origin()._y - y) < eps) && (fabs(ray.origin()._z - z) < eps);
}

bool CheckRayDirection(const Ray& ray, float x, float y, float z, float eps = Vec4::s_epsilon) {
	return (fabs(ray.direction()._x - x) < eps) && (fabs(ray.direction()._y - y) < eps) &&
	       (fabs(ray.direction()._z - z) < eps);
}

bool CheckRayPosAtT(const Ray& ray, float t, float x, float y, float z, float eps = Vec4::s_epsilon) {
	return (fabs(ray.Position(t)._x - x) < eps) && (fabs(ray.Position(t)._y - y) < eps) &&
	       (fabs(ray.Position(t)._z - z) < eps);
}

int main() {
	Ray ray1 = Ray(MakePoint(Vec4(1.0f, 2.0f, 3.0f)), MakeDir(Vec4(4.0f, 5.0f, 6.0f)));
	if(CheckRayOrigin(ray1, 1.0f, 2.0f, 3.0f) && CheckRayDirection(ray1, 4.0f, 5.0f, 6.0f)) {
		std::cout << GREEN << "Passed! " << "Ray is initialized with correct origin and direction." << RESET << std::endl;
	} else {
		std::cerr << RED << "Failed! " << "Ray is not initialized with correct origin and direction." << RESET << std::endl;
	}

	// check ray's position at different T values
	Ray ray2 = Ray(MakePoint(Vec4(0.0f, 0.0f, 0.0f)), MakeDir(Vec4(1.0f, 0.0f, 0.0f)));
	if(CheckRayPosAtT(ray2, 0.0f, 0.0f, 0.0f, 0.0f) && CheckRayPosAtT(ray2, 1.0f, 1.0f, 0.0f, 0.0f) &&
	   CheckRayPosAtT(ray2, 2.0f, 2.0f, 0.0f, 0.0f) && CheckRayPosAtT(ray2, 3.5f, 3.5f, 0.0f, 0.0f)) {
		std::cout << GREEN << "Passed! " << "Ray is at the correct position at all tested t values." << RESET << std::endl;
	} else {
		std::cerr << RED << "Failed! " << "Ray is not at the correct position at all tested t values." << RESET << std::endl;
	}

	return 0;
}