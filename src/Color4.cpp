#include "../include/Color4.hpp"

#include <cmath>

namespace MIRT {


float Color4::R() const { return _rgbaComponents._x; }
float Color4::G() const { return _rgbaComponents._y; }
float Color4::B() const { return _rgbaComponents._z; }
float Color4::A() const { return _rgbaComponents._w; }

float Color4::r() const { return R(); }
float Color4::g() const { return G(); }
float Color4::b() const { return B(); }
float Color4::a() const { return A(); }

void Color4::R(float value) { _rgbaComponents._x = value; }
void Color4::G(float value) { _rgbaComponents._y = value; }
void Color4::B(float value) { _rgbaComponents._z = value; }
void Color4::A(float value) { _rgbaComponents._w = value; }

void Color4::SetRGBA(float r, float g, float b, float a) {
	_rgbaComponents._x = r;
	_rgbaComponents._y = g;
	_rgbaComponents._z = b;
	_rgbaComponents._w = a;
}

Color4 Color4::operator+(const Color4& other) const {
	return Color4(r() + other.r(), g() + other.g(), b() + other.b(), a() + other.a());
}

Color4 Color4::operator-(const Color4& other) const {
	return Color4(r() - other.r(), g() - other.g(), b() - other.b(), a() - other.a());
}

Color4 Color4::operator*(const Color4& other) const {
	return Color4(r() * other.r(), g() * other.g(), b() * other.b(), a() * other.a());
}

Color4 Color4::operator*(float scalar) const { return Color4(r() * scalar, g() * scalar, b() * scalar, a() * scalar); }

Color4 Color4::operator/(const Color4& other) const {
	return Color4(r() / other.r(), g() / other.g(), b() / other.b(), a() / other.a());
}

Color4 Color4::operator/(float scalar) const { return Color4(r() / scalar, g() / scalar, b() / scalar, a() / scalar); }

bool Color4::operator==(const Color4& other) const {
	return (fabs(r() - other.r()) < Vec4::s_epsilon) && (fabs(g() - other.g()) < Vec4::s_epsilon) &&
	       (fabs(b() - other.b()) < Vec4::s_epsilon) && (fabs(a() - other.a()) < Vec4::s_epsilon);
}

bool Color4::operator!=(const Color4& other) const { return !(*this == other); }

std::string ToString(const Color4& color) {
	return "Color4(" + std::to_string(color.r()) + ", " + std::to_string(color.g()) + ", " + std::to_string(color.b()) + ", " +
	       std::to_string(color.a()) + ")";
}

}// namespace MIRT