#pragma once

#include "Vec4.hpp"

#include <glm/ext/matrix_float4x4.hpp>// mat4

namespace MIRT {

class Ray {
public:
	Ray() : _origin(MakePoint()), _direction(MakeDir()) {}
	Ray(const Vec4& origin, const Vec4& direction) : _origin(origin), _direction(direction) {}

	Vec4 origin() const;
	Vec4 direction() const;

	Vec4 Position(float t) const;

private:
	Vec4 _origin;
	Vec4 _direction;
};

Ray ApplyMatrixToRay(Ray r, glm::mat4 m);

}// namespace MIRT