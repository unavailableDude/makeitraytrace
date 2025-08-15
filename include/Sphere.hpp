#pragma once

#include <vector>

#include "Ray.hpp"
#include "Vec4.hpp"
#include "RayHit.hpp"

namespace MIRT {

class Sphere {
public:
	Sphere() : _center(MakePoint()), _radius(1.0f) {}
	Sphere(const Vec4& center, float radius) : _center(center), _radius(radius) {}

	Vec4 Center() const;
	float Radius() const;

	std::vector<RayHit> Intersect(const Ray& ray);

private:
	Vec4 _center;
	float _radius;
};

}// namespace MIRT