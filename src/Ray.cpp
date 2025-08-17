#include "../include/Ray.hpp"

namespace MIRT {

Vec4 Ray::origin() const { return _origin; }
Vec4 Ray::direction() const { return _direction; }

Vec4 Ray::Position(float t) const { return _origin + (_direction * t); }

Ray ApplyMatrixToRay(Ray r, glm::mat4 m) {
	// Apply the transformation matrix to the ray's origin and direction
	Vec4 origin = r.origin();
	Vec4 direction = r.direction();
	glm::vec4 newOrigin = glm::vec4(origin._x, origin._y, origin._z, origin._w) * m;
	glm::vec4 newDirection = glm::vec4(direction._x, direction._y, direction._z, direction._w) * m;

	return Ray(MakeVec4(newOrigin), MakeVec4(newDirection));
}

}// namespace MIRT