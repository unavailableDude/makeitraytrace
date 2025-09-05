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

	// add two concentric spheres, one with r = 1, one with r = 0.5
	// intersecting with ray at (0, 0, -5) in direction (0, 0, 1) should give 4 intersections
	// at t = 4, 6 for the big sphere and t = 4.5, 5.5 for the small sphere
	scene.AddSphere(Sphere());
	scene.AddSphere(Sphere(glm::transpose(glm::scale(glm::identity<glm::mat4>(), glm::vec3(0.5f, 0.5f, 0.5f)))));
	std::vector<RayHit> hits = scene.IntersectWorld(Ray(Vec4(0.0f, 0.0f, -5.0f, 1.0f), Vec4(0.0f, 0.0f, 1.0f, 0.0f)));
	if(hits.size() == 4 && hits[0].T() == 4.0f && hits[1].T() == 4.5f && hits[2].T() == 5.5f && hits[3].T() == 6.0f)
		std::cout << GREEN << "Passed: Scene could be intersected with ray correctly" << RESET << std::endl;
	else
		std::cout << RED << "Failed: Scene could not be intersected with ray correctly" << RESET << std::endl;

	return 0;
}