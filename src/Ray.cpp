#include "../include/Ray.hpp"

namespace MIRT {

Vec4 Ray::origin() const { return _origin; }
Vec4 Ray::direction() const { return _direction; }

Vec4 Ray::Position(float t) const { return _origin + (_direction * t); }

}// namespace MIRT