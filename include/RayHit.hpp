#pragma once


#include <limits>
#include <vector>

namespace MIRT {
// #include "Sphere.hpp"
class Sphere;


class RayHit {
public:
	RayHit();
	RayHit(float t);

	float T() const;
	Sphere* Object() const;

	// std::vector<Vec4> points;
	float t;
	Sphere* object;
};

// returns the first hit infront of the ray origin (smallest positive t)
RayHit FrontHit(std::vector<RayHit> hits);

}// namespace MIRT