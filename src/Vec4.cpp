#include "../include/Vec4.hpp"
#include <cmath>
namespace RTCE {


Vec4 Vec4::operator+(const Vec4& other) const { return Vec4(_x + other._x, _y + other._y, _z + other._z, _w + other._w); }
Vec4 Vec4::operator-(const Vec4& other) const { return Vec4(_x - other._x, _y - other._y, _z - other._z, _w - other._w); }
Vec4 Vec4::operator-() const { return Vec4(-_x, -_y, -_z, -_w); }
Vec4 Vec4::operator*(float scalar) const { return Vec4(_x * scalar, _y * scalar, _z * scalar, _w * scalar); }
Vec4 Vec4::operator/(float scalar) const {
	if(scalar == 0.0f) return Vec4(0.0f, 0.0f, 0.0f, 0.0f);
	return Vec4(_x / scalar, _y / scalar, _z / scalar, _w / scalar);
}

float Vec4::Magnitude() const { return sqrtf(_x * _x + _y * _y + _z * _z + _w * _w); }

Vec4 MakePoint(Vec4 v) {
	return Vec4(v._x, v._y, v._z, 1.0f);// w = 1 for positions
}

Vec4 MakeDir(Vec4 v) {
	return Vec4(v._x, v._y, v._z, 0.0f);// w = 0 for directions
}

// take epsilon into account
const bool IsVec4Equal(Vec4 a, Vec4 b) {
	return ((fabs(a._x - b._x) < Vec4::epsilon) && (fabs(a._y - b._y) < Vec4::epsilon) &&
	        (fabs(a._z - b._z) < Vec4::epsilon) && (fabs(a._w - b._w) < Vec4::epsilon));
}

}// namespace RTCE