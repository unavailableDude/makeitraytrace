#include "../include/Ray.hpp"

namespace RTCE {

Vec4 Ray::origin() const { return _origin; }
Vec4 Ray::direction() const { return _direction; }

}// namespace RTCE