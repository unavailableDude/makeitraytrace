#include "Scene.hpp"


namespace MIRT {


Sphere GenerateRandom(uint16_t id);


Scene::Scene() : _spheres(), _camera() {}

void Scene::SetSpheres(const std::vector<Sphere>& spheres) { _spheres = spheres; }

void Scene::GenerateRandomSpheres(uint16_t amount) {
	_spheres.clear();
	for(uint16_t i = 0; i < amount; ++i) {
		_spheres.push_back(GenerateRandom(i));
	}
}

void Scene::AddSphere(const Sphere& sphere) { _spheres.push_back(sphere); }
void Scene::ClearSpheres() { _spheres.clear(); }
Sphere& Scene::GetSphere(uint16_t id) { return _spheres.at(id); }
std::vector<Sphere> Scene::GetSpheres() const { return _spheres; }

void Scene::SetDefaultCamera() {
	_camera = Camera(Vec4(0.0f, 0.0f, 4.0f, 1.0f),
	                 Vec4(0.0f, 0.0f, -1.0f, 0.0f),
	                 Vec4(1.0f, 0.0f, 0.0f, 0.0f),
	                 Vec4(0.0f, 1.0f, 0.0f, 0.0f));
}
void Scene::SetCamera(const Camera& camera) { _camera = camera; }
Camera& Scene::GetCamera() { return _camera; }


Sphere GenerateRandom(uint16_t id) {
	Sphere sphere;
	// pick a random position from [-5, 5]
	float x = static_cast<float>((rand() / static_cast<float>(RAND_MAX)) * 10.0f) - 5.0f;
	float y = static_cast<float>((rand() / static_cast<float>(RAND_MAX)) * 10.0f) - 5.0f;
	float z = static_cast<float>((rand() / static_cast<float>(RAND_MAX)) * 2.0f) - 1.0f;
	// scale factor in range [0.5, 1.5]
	float scaleFactorX = static_cast<float>((rand() / static_cast<float>(RAND_MAX)) + 0.5f);
	float scaleFactorY = static_cast<float>((rand() / static_cast<float>(RAND_MAX)) + 0.5f);
	float scaleFactorZ = static_cast<float>((rand() / static_cast<float>(RAND_MAX)) + 0.5f);
	Vec4 position = Vec4(x, y, z, 1.0f);
	Vec4 scale = Vec4(scaleFactorX, scaleFactorY, scaleFactorZ, 1.0f);
	Material material;
	material.SetAmbient(0.1f);
	material.SetDiffuse(0.9f);
	material.SetSpecular(0.9f);
	material.SetShininess(32.0f);
	Color4 color = Color4(((static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) + 1.0f) / 2.0f,
	                      ((static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) + 1.0f) / 2.0f,
	                      ((static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) + 1.0f) / 2.0f,
	                      1.0f);
	material.SetSurfaceColor(color);
	sphere.SetTransform(position, scale);
	sphere.SetMaterial(material);
	sphere.SetId(id);
	return sphere;
}

}// namespace MIRT