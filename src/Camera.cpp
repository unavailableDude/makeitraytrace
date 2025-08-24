#include "Camera.hpp"


namespace MIRT {


Camera::Camera() : _position(0, 0, 0, 1), _forward(0, 0, -1, 0), _right(1, 0, 0, 0), _up(0, 1, 0, 0) {}

Camera::Camera(const Vec4& position, const Vec4& forward, const Vec4& right, const Vec4& up)
    : _position(position),
      _forward(forward),
      _right(right),
      _up(up) {}

Vec4 Camera::Position() const { return _position; }
Vec4 Camera::Forward() const { return _forward; }
Vec4 Camera::Right() const { return _right; }
Vec4 Camera::Up() const { return _up; }

void Camera::SetPosition(const Vec4& position) { _position = position; }
void Camera::SetForward(const Vec4& forward) { _forward = forward; }
void Camera::SetRight(const Vec4& right) { _right = right; }
void Camera::SetUp(const Vec4& up) { _up = up; }


}// namespace MIRT