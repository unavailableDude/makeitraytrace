#pragma once

#include <vector>

#include "Ray.hpp"
#include "RayHit.hpp"

#include <glm/ext/matrix_float4x4.hpp>// mat4
#include <glm/ext/matrix_transform.hpp>


namespace MIRT {

class Sphere {
public:
	Sphere() : _transform(glm::identity<glm::mat4>()) {}
	// expects row-major matrix
	Sphere(const glm::mat4& transform) : _transform(transform) {}

	glm::mat4 GetTransform() const;
	// expects row-major matrix
	void SetTransform(const glm::mat4& transform);

	std::vector<RayHit> Intersect(const Ray& ray);
	Vec4 NormalAtPoint(const Vec4& point) const;

private:
	glm::mat4 _transform;// row-major ordered
};

}// namespace MIRT