#pragma once

#include "Vec4.hpp"

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

}// namespace MIRT