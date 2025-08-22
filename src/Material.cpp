#include <Material.hpp>


namespace MIRT {


Material::Material()
    : _surfaceColor(Color4(1.0f, 1.0f, 1.0f, 1.0f)),
      _ambient(0.1f),
      _diffuse(0.9f),
      _specular(0.9),
      _shininess(100.0f) {}

Color4 Material::SurfaceColor() const { return _surfaceColor; }
float Material::Ambient() const { return _ambient; }
float Material::Diffuse() const { return _diffuse; }
float Material::Specular() const { return _specular; }
float Material::Shininess() const { return _shininess; }

void Material::SetSurfaceColor(const Color4& color) { _surfaceColor = color; }
void Material::SetAmbient(float ambient) { _ambient = ambient; }
void Material::SetDiffuse(float diffuse) { _diffuse = diffuse; }
void Material::SetSpecular(float specular) { _specular = specular; }
void Material::SetShininess(float shininess) { _shininess = shininess; }

}// namespace MIRT