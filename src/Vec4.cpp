#include "../include/Vec4.hpp"


#include <cmath>
#include <iostream>

namespace MIRT {


Vec4 Vec4::operator+(const Vec4& other) const { return Vec4(_x + other._x, _y + other._y, _z + other._z, _w + other._w); }
Vec4 Vec4::operator-(const Vec4& other) const { return Vec4(_x - other._x, _y - other._y, _z - other._z, _w - other._w); }
Vec4 Vec4::operator-() const { return Vec4(-_x, -_y, -_z, -_w); }// negation op, eg: vec4 a; a = -a;
Vec4 Vec4::operator*(float scalar) const { return Vec4(_x * scalar, _y * scalar, _z * scalar, _w * scalar); }
Vec4 Vec4::operator/(float scalar) const {
	if(scalar == 0.0f) return Vec4(0.0f, 0.0f, 0.0f, 0.0f);
	return Vec4(_x / scalar, _y / scalar, _z / scalar, _w / scalar);
}

float Vec4::Magnitude() const { return sqrtf(_x * _x + _y * _y + _z * _z + _w * _w); }

Vec4& Vec4::Normalize() {
	float mag = this->Magnitude();
	this->_x /= mag;
	this->_y /= mag;
	this->_z /= mag;
	this->_w /= mag;
	return *this;
}

float Dot(Vec4 a, Vec4 b) { return (a._x * b._x + a._y * b._y + a._z * b._z + a._w * b._w); }

Vec4 Cross(Vec4 a, Vec4 b) {
	if(a._w != 0.0f || b._w != 0.0f) std::cerr << "tied to Vec4::Cross a vector with w != 0\n";// big no-no
	return Vec4(a._y * b._z - a._z * b._y, a._z * b._x - a._x * b._z, a._x * b._y - a._y * b._x,
	            0.0f);// w = 0 for directions
}

Vec4 MakePoint(Vec4 v) {
	return Vec4(v._x, v._y, v._z, 1.0f);// w = 1 for positions
}

Vec4 MakeDir(Vec4 v) {
	return Vec4(v._x, v._y, v._z, 0.0f);// w = 0 for directions
}

// take s_epsilon into account
const bool IsVec4Equal(Vec4 a, Vec4 b, float epsilon) {
	return ((fabs(a._x - b._x) < epsilon) && (fabs(a._y - b._y) < epsilon) && (fabs(a._z - b._z) < epsilon) &&
	        (fabs(a._w - b._w) < epsilon));
}

}// namespace MIRT