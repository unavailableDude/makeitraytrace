#pragma once
/*
    this object represents a 3d scene, composed of various objects (spheres, lights, and cameras)
*/

#include <vector>
#include <cstdint>

#include "Sphere.hpp"
#include "Camera.hpp"
#include "RayHit.hpp"


namespace MIRT {


class Scene {
public:
	Scene();
	void SetSpheres(const std::vector<Sphere>& spheres);
	void GenerateRandomSpheres(uint16_t amount);
	void AddSphere(const Sphere& sphere);
	void ClearSpheres();
	Sphere& GetSphere(uint16_t id);        // id same as index in _spheres
	std::vector<Sphere> GetSpheres() const;// tested by Sphere

	void SetDefaultCamera();
	void SetCamera(const Camera& camera);
	Camera& GetCamera();

	std::vector<RayHit> IntersectWorld(const Ray& ray);

private:
	std::vector<Sphere> _spheres;
	Camera _camera;
};

}// namespace MIRT