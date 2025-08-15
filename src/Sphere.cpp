#include <cmath>

#include "../include/Sphere.hpp"

namespace MIRT {

Vec4 Sphere::Center() const { return _center; }

float Sphere::Radius() const { return _radius; }

std::vector<RayHit> Sphere::Intersect(const Ray& ray) {
	std::vector<RayHit> hits;

	Vec4 oc = ray.origin() - Center();
	float a = MIRT::Dot(ray.direction(), ray.direction());
	float b = 2.0f * MIRT::Dot(oc, ray.direction());
	float c = MIRT::Dot(oc, oc) - Radius() * Radius();
	float discriminant = b * b - 4 * a * c;

	if(discriminant < 0) {
		// No intersection
		return hits;
	}

	// Calculate the two intersection points
	float sqrtDiscriminant = sqrt(discriminant);
	float t1 = (-b - sqrtDiscriminant) / (2.0f * a);
	float t2 = (-b + sqrtDiscriminant) / (2.0f * a);

	RayHit hit1;
	hit1.t = t1;
	hit1.object = this;

	RayHit hit2;
	hit2.t = t2;
	hit2.object = this;

	hits.push_back(hit1);
	hits.push_back(hit2);

	return hits;
}

}// namespace MIRT