#pragma once


#include <limits>

namespace MIRT {
// #include "Sphere.hpp"
class Sphere;


class RayHit {
public:
	RayHit();

	float T() const;
	Sphere* Object() const;

	// std::vector<Vec4> points;
	float t;
	Sphere* object;
};

}// namespace MIRT