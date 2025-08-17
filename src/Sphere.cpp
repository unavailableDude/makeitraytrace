#include <cmath>

#include "../include/Sphere.hpp"


namespace MIRT {

glm::mat4 Sphere::GetTransform() const { return _transform; }
void Sphere::SetTransform(const glm::mat4& transform) { _transform = transform; }

std::vector<RayHit> Sphere::Intersect(const Ray& ray) {
	std::vector<RayHit> hits;

	// apply the inverse of the sphere transformation to the ray, then calculate intersection.
	Ray transformedRay = ApplyMatrixToRay(ray, glm::inverse(_transform));
	Vec4 oc = transformedRay.origin() - MakeVec4(_transform[3]);
	float a = MIRT::Dot(transformedRay.direction(), transformedRay.direction());
	float b = 2.0f * MIRT::Dot(oc, transformedRay.direction());
	float c = MIRT::Dot(oc, oc) - 1.0f;
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