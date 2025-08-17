#include <iostream>
#include <cmath>
#include <vector>

#include "../include/Ray.hpp"
#include "../include/Sphere.hpp"
#include "../include/Vec4.hpp"
#include "../include/RayHit.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>


// ANSI color codes
#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"

using namespace MIRT;


bool CheckSphereInitialTransform(const Sphere& sphere, glm::mat4 expectedTransform) {
	return sphere.GetTransform() == expectedTransform;
}

bool CheckHitDistance(const RayHit& hit, float distance, float eps = Vec4::s_epsilon) {
	return std::abs(hit.T() - distance) < eps;
}

bool CheckHitDistanceOver(const RayHit& hit, float threshold) { return hit.T() > threshold; }

int main() {
	Sphere sphere1 = Sphere();
	if(CheckSphereInitialTransform(sphere1, glm::identity<glm::mat4>())) {
		std::cout << GREEN << "Passed! " << "Sphere is initialized with correct transform." << RESET << std::endl;
	} else {
		std::cout << RED << "Failed! " << "Sphere is not initialized with correct transform." << RESET << std::endl;
	}

	// this intersection should yield 2 points at (0, 0, -1) and (0, 0, 1), t1 = 4 & t2 = 6
	Ray ray1 = Ray(MakePoint(Vec4(0.0f, 0.0f, -5.0f)), MakeDir(Vec4(0.0f, 0.0f, 1.0f)));
	std::vector<RayHit> hits = sphere1.Intersect(ray1);
	if(CheckHitDistance(hits[0], 4.0f) && CheckHitDistance(hits[1], 6.0f)) {
		std::cout << GREEN << "Passed! " << "Ray intersects the sphere at the correct distance." << RESET << std::endl;
	} else {
		std::cout << RED << "Failed! " << "Ray does not intersect the sphere at the correct distance." << RESET << std::endl;
	}

	// this intersection should yield one point at (0, 1, 0)
	Ray ray2 = Ray(MakePoint(Vec4(0.0f, 1.0f, -5.0f)), MakeDir(Vec4(0.0f, 0.0f, 1.0f)));
	hits = sphere1.Intersect(ray2);
	if(CheckHitDistance(hits[0], 5.0f)) {
		std::cout << GREEN << "Passed! " << "Ray glances the sphere at the correct point." << RESET << std::endl;
	} else {
		std::cout << RED << "Failed! " << "Ray does not glances the sphere at the correct point." << RESET << std::endl;
	}

	// this intersection should yield no points, as the ray misses the sphere
	Ray ray3 = Ray(MakePoint(Vec4(2.0f, 2.0f, -5.0f)), MakeDir(Vec4(0.0f, 0.0f, 1.0f)));
	hits = sphere1.Intersect(ray3);
	if(hits.empty()) {
		std::cout << GREEN << "Passed! " << "Ray misses the sphere as expected." << RESET << std::endl;
	} else {
		std::cout << RED << "Failed! " << "Ray should not intersect the sphere." << RESET << std::endl;
	}

	// a ray inside the sphere still intersects at 2 points, t1 = -1, t2 = 1
	Ray ray4 = Ray(MakePoint(Vec4(0.0f, 0.0f, 0.0f)), MakeDir(Vec4(0.0f, 0.0f, 1.0f)));
	hits = sphere1.Intersect(ray4);
	if(CheckHitDistance(hits[0], -1.0f) && CheckHitDistance(hits[1], 1.0f)) {
		std::cout << GREEN << "Passed! "
		          << "a Ray that is inside the sphere should intersect at 2 points, with -t1, +t2" << RESET << std::endl;
	} else {
		std::cout << RED << "Failed! "
		          << "a Ray that is inside the sphere should intersect at 2 points, with -t1, +t2" << RESET << std::endl;
	}

	// a ray infront of the sphere should still have 2 hit behind it with the sphere, both t are negative, t1 = -6, t2 = -4
	Ray ray5 = Ray(MakePoint(Vec4(0.0f, 0.0f, 5.0f)), MakeDir(Vec4(0.0f, 0.0f, 1.0f)));
	hits = sphere1.Intersect(ray5);
	if(CheckHitDistance(hits[0], -6.0f) && CheckHitDistance(hits[1], -4.0f)) {
		std::cout << GREEN << "Passed! "
		          << "a Ray that is in front of the sphere should intersect at 2 points, both t are negative" << RESET
		          << std::endl;
	} else {
		std::cout << RED << "Failed! "
		          << "a Ray that is in front of the sphere should intersect at 2 points, both t are negative" << RESET
		          << std::endl;
	}

	// when transforming a sphere to (0, 1, 0), a ray ((0, 0, -3), (0, 0, 1)) should hit at (0, 1, 0)
	Ray ray6 = Ray(MakePoint(Vec4(0.0f, 0.0f, -3.0f)), MakeDir(Vec4(0.0f, 0.0f, 1.0f)));
	Sphere sphere2 = Sphere();
	sphere2.SetTransform(glm::translate(glm::identity<glm::mat4>(), glm::vec3(0.0f, 1.0f, 0.0f)));
	hits = sphere2.Intersect(ray6);
	if(CheckHitDistance(hits[0], 3.0f)) {
		std::cout << GREEN << "Passed! " << "Ray intersects the transformed sphere at the correct point." << RESET
		          << std::endl;
	} else {
		std::cout << RED << "Failed! " << "Ray does not intersect the transformed sphere at the correct point." << RESET
		          << std::endl;
	}

	// when the sphere is scaled by (2, 2, 2), the ray ((0, 0, -3), (0, 0, 1)) should hit at (-2, 0, 0) and (2, 0, 0)
	glm::mat4 scaling = glm::scale(glm::identity<glm::mat4>(), glm::vec3(2.0f, 2.0f, 2.0f));
	glm::mat4 transform = glm::transpose(scaling);// convert it to row-major
	std::cout << glm::to_string(transform) << std::endl;
	sphere2.SetTransform(transform);
	hits = sphere2.Intersect(ray6);
	if(CheckHitDistance(hits[0], 1.0f) && CheckHitDistance(hits[1], 5.0f)) {
		std::cout << GREEN << "Passed! "
		          << "Ray intersects the scaled sphere at the correct points." << RESET << std::endl;
	} else {
		std::cout << RED << "Failed! "
		          << "Ray does not intersect the scaled sphere at the correct points, expected hit distances (1, 5), got ("
		          << hits[0].T() << ", " << hits[1].T() << ")" << RESET << std::endl;
	}

	// when the sphere is scaled by (2, 2, 2) then translated by (0, 2, 0),
	// the ray ((0, 0, -3), (0, 0, 1)) should hit at (0, 0, 0)
	glm::mat4 translation = glm::translate(glm::identity<glm::mat4>(), glm::vec3(0.0f, 2.0f, 0.0f));
	transform = glm::transpose(translation * scaling);// convert it to row-major
	sphere2.SetTransform(transform);
	hits = sphere2.Intersect(ray6);
	if(CheckHitDistance(hits[0], 3.0f)) {
		std::cout << GREEN << "Passed! "
		          << "Ray intersects the scaled and translated sphere at the correct point." << RESET << std::endl;
	} else {
		std::cout
		    << RED << "Failed! "
		    << "Ray does not intersect the scaled and translated sphere at the correct point, expected hit distances (3), got ("
		    << hits[0].T() << ")" << RESET << std::endl;
	}
}
