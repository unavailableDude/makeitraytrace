#include <cmath>

#include "../include/Sphere.hpp"
#include "Vec4.hpp"

#include "../include/glm/matrix.hpp"


namespace MIRT {

Material Sphere::GetMaterial() const { return _material; }
void Sphere::SetMaterial(const Material& material) { _material = material; }
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

	Vec4 point1 = transformedRay.Position(t1);
	Vec4 point2 = transformedRay.Position(t2);

	// for some reason, ignoring the w component while calculating the normal of an intersection point, having a w component
	// messes up the normal
	Vec4 normal1 = NormalAtPoint(point1, true);
	Vec4 normal2 = NormalAtPoint(point2, true);

	RayHit hit1(t1, point1, normal1, this);
	RayHit hit2(t2, point2, normal2, this);

	hits.push_back(hit1);
	hits.push_back(hit2);

	return hits;
}

Vec4 Sphere::NormalAtPoint(const Vec4& point, bool ignoreW) const {
	// remember, glm uses column-major order, but we use row-major, so we convert a row-major matrix to column major before we
	// use it with glm, and also we convert the result of glm to row-major before we use it

	// to get the normal, we get the object-space point, by inverse transforming it using the object's transform matrix,
	// then we find the normal at that point for a sphere it is (point - center), then we transform this normal by the
	// transpose of the inverse of the transform matrix, then we set the w component to 0 to avoid some problems
	Vec4 wsPoint = point;
	if(ignoreW) wsPoint._w = 0.0f;
	glm::mat4 transformCM = glm::transpose(_transform);
	Vec4 osPoint = MakeVec4(glm::inverse(transformCM) * MakeGLMVec4(wsPoint));
	Vec4 osNormal = osPoint - Vec4(0.0f, 0.0f, 0.0f, 1.0f);
	osNormal._w = 0.0f;
	osNormal = MakeVec4(glm::transpose(glm::inverse(transformCM)) * MakeGLMVec4(osNormal));
	osNormal._w = 0.0f;
	return osNormal.Normalize();
}

}// namespace MIRT