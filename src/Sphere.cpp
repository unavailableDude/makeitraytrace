#include <cmath>

#include "../include/Sphere.hpp"

namespace MIRT {

Vec4 Sphere::Center() const { return _center; }

float Sphere::Radius() const { return _radius; }

RayHit Sphere::Intersect(const Ray& ray) {
	RayHit hit;

	Vec4 oc = ray.origin() - Center();
	float a = MIRT::Dot(ray.direction(), ray.direction());
	float b = 2.0f * MIRT::Dot(oc, ray.direction());
	float c = MIRT::Dot(oc, oc) - Radius() * Radius();
	float discriminant = b * b - 4 * a * c;

	if(discriminant < 0) {
		// No intersection
		return hit;
	}

	// Calculate the two intersection points
	float sqrtDiscriminant = sqrt(discriminant);
	float t1 = (-b - sqrtDiscriminant) / (2.0f * a);
	// float t2 = (-b + sqrtDiscriminant) / (2.0f * a);

	hit.t = t1;
	hit.object = this;

	return hit;
}

}// namespace MIRT