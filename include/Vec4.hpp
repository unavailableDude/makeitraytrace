#pragma once

namespace RTCE {

// w = 1 for positions, w = 0 for directions
struct Vec4 {
	float _x;
	float _y;
	float _z;
	float _w;
	static constexpr float epsilon = 0.00001f;

	Vec4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f) : _x(x), _y(y), _z(z), _w(w) {}


	Vec4 operator+(const Vec4& other) const;
	Vec4 operator-(const Vec4& other) const;
	Vec4 operator-() const;// negates x, y, z, w
	Vec4 operator*(float scalar) const;
	Vec4 operator/(float scalar) const;

	float Magnitude() const;
};

Vec4 MakePoint(Vec4 v = Vec4(0.0f, 0.0f, 0.0f));
Vec4 MakeDir(Vec4 v = Vec4(0.0f, 0.0f, -1.0f));

const bool IsVec4Equal(Vec4 a, Vec4 b);

}// namespace RTCE