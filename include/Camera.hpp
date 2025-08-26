#pragma once


#include "Vec4.hpp"


namespace MIRT {


class Camera {
public:
	Camera();
	Camera(const Vec4& position, const Vec4& forward, const Vec4& right, const Vec4& up);

	Vec4 Position() const;
	Vec4 Forward() const;
	Vec4 Right() const;
	Vec4 Up() const;

	void SetPosition(const Vec4& position);
	void SetForward(const Vec4& forward);
	void SetRight(const Vec4& right);
	void SetUp(const Vec4& up);

	std::vector<Vec4> GetCameraVectors() const;

private:
	Vec4 _position;
	Vec4 _forward;
	Vec4 _right;
	Vec4 _up;
};

}// namespace MIRT