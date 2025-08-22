#pragma once


#include "Color4.hpp"


namespace MIRT {


class Material {
public:
	Material();

	Color4 SurfaceColor() const;
	float Ambient() const;
	float Diffuse() const;
	float Specular() const;
	float Shininess() const;

	void SetSurfaceColor(const Color4& color);
	void SetAmbient(float ambient);
	void SetDiffuse(float diffuse);
	void SetSpecular(float specular);
	void SetShininess(float shininess);

private:
	Color4 _surfaceColor;
	float _ambient;
	float _diffuse;
	float _specular;
	float _shininess;
};


}// namespace MIRT