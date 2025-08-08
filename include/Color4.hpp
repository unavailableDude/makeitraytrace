#include "Vec4.hpp"


namespace RTCE {


class Color4 {
public:
	Color4(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 0.0f) : _rgbaComponents(r, g, b, a) {}

	// access components in multiple ways
	float R() const;
	float G() const;
	float B() const;
	float A() const;

	float r() const;
	float g() const;
	float b() const;
	float a() const;

	Color4 operator+(const Color4& other) const;
	Color4 operator-(const Color4& other) const;
	Color4 operator*(const Color4& other) const;// hadamard product
	Color4 operator*(float scalar) const;
	Color4 operator/(const Color4& other) const;// hadamard product
	Color4 operator/(float scalar) const;

private:
	Vec4 _rgbaComponents;
};

}// namespace RTCE