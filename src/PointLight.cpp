#include "PointLight.hpp"


namespace MIRT {


Color4 PointLight::GetIntensity() const { return _intensity; }
Vec4 PointLight::GetPosition() const { return _position; }

}// namespace MIRT