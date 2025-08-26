#include "PointLight.hpp"


namespace MIRT {


Color4 PointLight::GetIntensity() const { return _intensity; }
Vec4 PointLight::GetPosition() const { return _position; }
std::vector<Vec4> PointLight::GetLightData() const {
	std::vector<Vec4> lightData;
	lightData.push_back(Vec4(_intensity.r(), _intensity.g(), _intensity.b(), _intensity.a()));
	lightData.push_back(_position);
	return lightData;
}

}// namespace MIRT