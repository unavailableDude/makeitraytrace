#include <iostream>
#include <cmath>
#include <vector>

#include "../include/Ray.hpp"
#include "../include/Sphere.hpp"
#include "../include/Vec4.hpp"
#include "../include/RayHit.hpp"


// ANSI color codes
#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"

using namespace MIRT;


bool CheckSpherePosition(const Sphere& sphere, const Vec4& point, float eps = Vec4::s_epsilon) {
	return (fabs(sphere.Center()._x - point._x) < eps) && (fabs(sphere.Center()._y - point._y) < eps) &&
	       (fabs(sphere.Center()._z - point._z) < eps);
}

bool CheckSphereRadius(const Sphere& sphere, float radius, float eps = Vec4::s_epsilon) {
	return std::abs(sphere.Radius() - radius) < eps;
}

bool CheckHitDistance(const RayHit& hit, float distance, float eps = Vec4::s_epsilon) {
	return std::abs(hit.T() - distance) < eps;
}

bool CheckHitDistanceOver(const RayHit& hit, float threshold) { return hit.T() > threshold; }

int main() {
	Sphere sphere1 = Sphere();
	if(CheckSpherePosition(sphere1, Vec4(0.0f, 0.0f, 0.0f)) && CheckSphereRadius(sphere1, 1.0f)) {
		std::cout << GREEN << "Passed! " << "Sphere is initialized with correct center and radius." << RESET << std::endl;
	} else {
		std::cout << RED << "Failed! " << "Sphere is not initialized with correct center and radius." << RESET << std::endl;
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
}