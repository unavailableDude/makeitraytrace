#pragma once


#include <glm/vec4.hpp>
#include <glm/vec3.hpp>

#include <string>

namespace MIRT {

// w = 1 for positions, w = 0 for directions
struct Vec4 {
	float _x;
	float _y;
	float _z;
	float _w;
	static constexpr float s_epsilon = 0.00001f;

	Vec4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f) : _x(x), _y(y), _z(z), _w(w) {}


	Vec4 operator+(const Vec4& other) const;
	Vec4 operator-(const Vec4& other) const;
	Vec4 operator-() const;// negates x, y, z, w
	Vec4 operator*(float scalar) const;
	Vec4 operator/(float scalar) const;
	bool operator==(const Vec4& other) const;

	float Magnitude() const;

	Vec4& Normalize();
};

float Dot(Vec4 a, Vec4 b);
Vec4 Cross(Vec4 a, Vec4 b);
Vec4 Reflect(const Vec4& incident, const Vec4& normal);

Vec4 MakePoint(Vec4 v = Vec4(0.0f, 0.0f, 0.0f));
Vec4 MakeDir(Vec4 v = Vec4(0.0f, 0.0f, -1.0f));

// convenience functions, to convert between glm::vec4 and MIRT::Vec4
Vec4 MakeVec4(const glm::vec4& v);
Vec4 MakeVec4(const glm::vec3& v);
glm::vec4 MakeGLMVec4(const Vec4& v);
glm::vec3 MakeGLMVec3(const Vec4& v);

const bool IsVec4Equal(Vec4 a, Vec4 b, float epsilon = Vec4::s_epsilon);
const std::string ToString(const Vec4& v);

}// namespace MIRT