#include "../include/Vec4.hpp"
namespace RTCE {


Vec4 Vec4::operator+(const Vec4& other) const { return Vec4(_x + other._x, _y + other._y, _z + other._z, _w + other._w); }
Vec4 Vec4::operator-(const Vec4& other) const { return Vec4(_x - other._x, _y - other._y, _z - other._z, _w - other._w); }


Vec4 MakePoint(Vec4 v) {
	return Vec4(v._x, v._y, v._z, 1.0f);// w = 1 for positions
}

Vec4 MakeDir(Vec4 v) {
	return Vec4(v._x, v._y, v._z, 0.0f);// w = 0 for directions
}
}// namespace RTCE