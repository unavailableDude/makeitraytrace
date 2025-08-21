#include "../include/RayHit.hpp"
#include "../include/Sphere.hpp"


namespace MIRT {

RayHit::RayHit() : _t(std::numeric_limits<float>::max()), _hitPoint(), _normal(), _object(nullptr) {}
RayHit::RayHit(float t) : _t(t), _hitPoint(), _normal(), _object(nullptr) {}
RayHit::RayHit(float t, const Vec4& hitPoint, const Vec4& normal, Sphere* object)
    : _t(t),
      _hitPoint(hitPoint),
      _normal(normal),
      _object(object) {}

float RayHit::T() const { return _t; }
Vec4 RayHit::HitPoint() const { return _hitPoint; }
Vec4 RayHit::Normal() const { return _normal; }
Sphere* RayHit::Object() const { return _object; }


RayHit FrontHit(const std::vector<RayHit>& hits) {
	if(hits.empty()) return RayHit();

	int idxOfClosestHit = -1;// if stays at -1, all found hits are negative
	float closestT = std::numeric_limits<float>::max();
	for(unsigned int i = 0; i < hits.size(); i++) {
		if(hits[i].T() > 0.0f && hits[i].T() < closestT) {
			closestT = hits[i].T();
			idxOfClosestHit = i;
		}
	}
	if(idxOfClosestHit < 0) {
		return RayHit();
	}
	return hits[idxOfClosestHit];
}

}// namespace MIRT