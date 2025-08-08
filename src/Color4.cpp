#include "../include/Color4.hpp"


namespace RTCE {


float Color4::R() const { return _rgbaComponents._x; }
float Color4::G() const { return _rgbaComponents._y; }
float Color4::B() const { return _rgbaComponents._z; }
float Color4::A() const { return _rgbaComponents._w; }

float Color4::r() const { return R(); }
float Color4::g() const { return G(); }
float Color4::b() const { return B(); }
float Color4::a() const { return A(); }

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

}// namespace RTCE