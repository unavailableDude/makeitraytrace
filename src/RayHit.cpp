#include "../include/RayHit.hpp"
#include "../include/Sphere.hpp"


namespace MIRT {

RayHit::RayHit() : t(10000000000.0f), object(nullptr) {}

float RayHit::T() const { return t; }
Sphere* RayHit::Object() const { return object; }

}// namespace MIRT