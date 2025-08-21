#pragma once


#include <limits>
#include <vector>

#include "Vec4.hpp"

namespace MIRT {
// #include "Sphere.hpp"
class Sphere;


class RayHit {
public:
	RayHit();
	RayHit(float t);
	RayHit(float t, const Vec4& hitPoint, const Vec4& normal, Sphere* object);

	float T() const;
	Vec4 HitPoint() const;
	Vec4 Normal() const;
	Sphere* Object() const;

	// std::vector<Vec4> points;
	float _t;
	Vec4 _hitPoint;
	Vec4 _normal;
	Sphere* _object;
};

// returns the first hit infront of the ray origin (smallest positive t)
RayHit FrontHit(const std::vector<RayHit>& hits);

}// namespace MIRT