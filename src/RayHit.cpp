#include "../include/RayHit.hpp"
#include "../include/Sphere.hpp"


namespace MIRT {

RayHit::RayHit() : t(std::numeric_limits<float>::max()), object(nullptr) {}
RayHit::RayHit(float t) : t(t), object(nullptr) {}

float RayHit::T() const { return t; }
Sphere* RayHit::Object() const { return object; }

RayHit FrontHit(std::vector<RayHit> hits) {
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