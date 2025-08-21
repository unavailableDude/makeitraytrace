#include <iostream>
#include <cmath>

#include <glm/ext/matrix_float4x4.hpp>// mat4
#include <glm/ext/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>// for glm::to_string

#include "../include/Ray.hpp"
#include "../include/Vec4.hpp"
#include "../include/Sphere.hpp"
#include "../include/RayHit.hpp"
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

int main(int argc, char* argv[]) {
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

	Sphere sphere1 = Sphere();
	Ray ray3 = Ray(MakePoint(Vec4(0.0f, 0.0f, -4.0f)), MakeDir(Vec4(0.0f, 0.0f, 1.0f)));
	std::vector<RayHit> hits1 = sphere1.Intersect(ray3);

	// ray3 should intersect twice with sphere1
	if(hits1[0].Object() == &sphere1 && hits1[1].Object() == &sphere1) {
		std::cout << GREEN << "Passed! " << "RayHit reports correct intersected object for 1 sphere." << RESET << std::endl;
	} else {
		std::cerr << RED << "Failed! " << "RayHit reports incorrect intersected object for 1 sphere." << RESET << std::endl;
	}

	// first front hit of ray3 with sphere1 is at t = 3
	if(FrontHit(hits1).T() == 3.0f) {
		std::cout << GREEN << "Passed! " << "FrontHit reports correct t value." << RESET << std::endl;
	} else {
		std::cerr << RED << "Failed! " << "FrontHit reports incorrect t value." << RESET << std::endl;
	}

	Ray ray4 = Ray(MakePoint(Vec4(0.0f, 0.0f, 4.0f)), MakeDir(Vec4(0.0f, 0.0f, 1.0f)));
	std::vector<RayHit> hits2 = sphere1.Intersect(ray4);

	// ray4 should intersect with sphere1 twice with negative t values, FrontHit should return empty hit
	if(FrontHit(hits2).T() >= std::numeric_limits<float>::max()) {
		std::cout << GREEN << "Passed! " << "FrontHit returns nothing for hits with negative t values." << RESET << std::endl;
	} else {
		std::cerr << RED << "Failed! " << "FrontHit shouldn't return a hit for hits with negative t." << RESET << std::endl;
	}

	// translating a ray at (1, 2, 3) by (3, 4, 5) gives position of (4, 6, 8)
	// note: matrix has to be transposed because glm orders the matrix in column-major order, but we use it in row-major order
	Ray ray5 = Ray(MakePoint(Vec4(1.0f, 2.0f, 3.0f)), MakeDir(Vec4(0.0f, 1.0f, 0.0f)));
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(3.0f, 4.0f, 5.0f));
	ray5 = ApplyMatrixToRay(ray5, glm::transpose(translationMatrix));
	if(CheckRayOrigin(ray5, 4.0f, 6.0f, 8.0f)) {
		std::cout << GREEN << "Passed! " << "Ray is translated to the correct origin." << RESET << std::endl;
	} else {
		std::cerr << RED << "Failed! " << "Ray is not translated to the correct origin." << RESET << std::endl;
	}
	// check ray's direction after translation
	if(CheckRayDirection(ray5, 0.0f, 1.0f, 0.0f)) {
		std::cout << GREEN << "Passed! " << "Ray direction is unchanged after translation." << RESET << std::endl;
	} else {
		std::cerr << RED << "Failed! " << "Ray direction is not unchanged after translation." << RESET << std::endl;
	}

	// scaling ray((1, 2, 3), (0, 1, 0)) by (2, 3, 4) should change its origin and direction to (2, 6, 12) and (0, 3, 0)
	glm::mat4 scalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 3.0f, 4.0f));
	Ray ray6 = Ray(MakePoint(Vec4(1.0f, 2.0f, 3.0f)), MakeDir(Vec4(0.0f, 1.0f, 0.0f)));
	ray6 = ApplyMatrixToRay(ray6, glm::transpose(scalingMatrix));
	if(CheckRayOrigin(ray6, 2.0f, 6.0f, 12.0f)) {
		std::cout << GREEN << "Passed! " << "Ray is scaled to the correct origin." << RESET << std::endl;
	} else {
		std::cerr << RED << "Failed! " << "Ray is not scaled to the correct origin." << RESET << std::endl;
	}
	// check ray's direction after scaling
	if(CheckRayDirection(ray6, 0.0f, 3.0f, 0.0f)) {
		std::cout << GREEN << "Passed! " << "Ray direction is scaled." << RESET << std::endl;
	} else {
		std::cerr << RED << "Failed! " << "Ray direction is not scaled." << RESET << std::endl;
	}

	return 0;
}