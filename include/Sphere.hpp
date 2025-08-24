#pragma once

#include <vector>
#include <cstdint>

#include "Ray.hpp"
#include "RayHit.hpp"
#include "Material.hpp"

#include <glm/ext/matrix_float4x4.hpp>// mat4
#include <glm/ext/matrix_transform.hpp>


namespace MIRT {

class Sphere {
public:
	Sphere() : _material(), _transform(glm::identity<glm::mat4>()), _id(0) {}
	// expects row-major matrix
	Sphere(const glm::mat4& transform) : _material(), _transform(transform), _id(0), _padding{0.0f} {}
	Sphere(const glm::mat4& transform, const Material& material)
	    : _material(material),
	      _transform(transform),
	      _id(0),
	      _padding{0.0f} {}
	Sphere(const glm::mat4& transform, const Material& material, uint32_t id)
	    : _material(material),
	      _transform(transform),
	      _id(id),
	      _padding{0.0f} {}

	Material GetMaterial() const;
	void SetMaterial(const Material& material);
	glm::mat4 GetTransform() const;
	// expects row-major matrix
	void SetTransform(const glm::mat4& transform);

	std::vector<RayHit> Intersect(const Ray& ray);
	Vec4 NormalAtPoint(const Vec4& point, bool ignoreW = false) const;

private:
	Material _material;
	glm::mat4 _transform;// row-major ordered
	uint32_t _id;        // 100 bytes up to here
	float _padding[7];   // 128 bytes up to here, (multiple of 16)
};

}// namespace MIRT