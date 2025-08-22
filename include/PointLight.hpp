#pragma once


#include "Color4.hpp"
#include "Vec4.hpp"


namespace MIRT {


class PointLight {
public:
	PointLight(const Color4& intensity = Color4(1.0f, 1.0f, 1.0f, 1.0f), const Vec4& position = Vec4(0.0f, 0.0f, 0.0f, 1.0f))
	    : _intensity(intensity),
	      _position(position) {}

	Color4 GetIntensity() const;
	Vec4 GetPosition() const;

private:
	Color4 _intensity;
	Vec4 _position;
};

}// namespace MIRT