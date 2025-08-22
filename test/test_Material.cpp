#include "Material.hpp"
#include "Color4.hpp"
#include "Vec4.hpp"

#include <iostream>
#include <math.h>


// ANSI color codes
#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"


using namespace MIRT;


// returns true for equal, takes s_epsilon into account
bool AssertColEqual(const Color4& col, float r, float g, float b, float a, float eps, const char* title = "") {
	if((fabs(col.r() - r) < eps) && (fabs(col.g() - g) < eps) && (fabs(col.b() - b) < eps) && (fabs(col.a() - a) < eps)) {
		std::cout << GREEN << "passed! " << title << RESET << std::endl;
		return true;
	}
	std::cerr << RED << "failed! " << title << " Expected: (" << r << ", " << g << ", " << b << ", " << a << "), Got: ("
	          << col.r() << ", " << col.g() << ", " << col.b() << ", " << col.a() << ")" << RESET << std::endl;
	return false;
}

bool AssertFloatEqual(const float& val, float expected, float eps, const char* title = "") {
	if(fabs(val - expected) < eps) {
		std::cout << GREEN << "passed! " << title << RESET << std::endl;
		return true;
	}
	std::cerr << RED << "failed! " << title << " Expected: " << expected << ", Got: " << val << RESET << std::endl;
	return false;
}

int main(int argc, char** argv) {
	MIRT::Material material;

	float eps = Vec4::s_epsilon;

	// Test default values
	AssertColEqual(material.SurfaceColor(),
	               1.0f,
	               1.0f,
	               1.0f,
	               1.0f,
	               eps,
	               "default surface color should be (1.0, 1.0, 1.0, 1.0)");

	AssertFloatEqual(material.Ambient(), 0.1f, eps, "default ambient should be 0.1");
	AssertFloatEqual(material.Diffuse(), 0.9f, eps, "default diffuse should be 0.9");
	AssertFloatEqual(material.Specular(), 0.9f, eps, "default specular should be 0.9");
	AssertFloatEqual(material.Shininess(), 100.0f, eps, "default shininess should be 100.0");

	// test values after changing them
	material.SetSurfaceColor(Color4(0.5f, 0.5f, 0.5f, 1.0f));
	material.SetAmbient(0.2f);
	material.SetDiffuse(0.8f);
	material.SetSpecular(0.8f);
	material.SetShininess(50.0f);

	AssertColEqual(material.SurfaceColor(),
	               0.5f,
	               0.5f,
	               0.5f,
	               1.0f,
	               eps,
	               "surface color should be (0.5, 0.5, 0.5, 1.0) after changing it");

	AssertFloatEqual(material.Ambient(), 0.2f, eps, "ambient should be 0.2 after changing it");
	AssertFloatEqual(material.Diffuse(), 0.8f, eps, "diffuse should be 0.8 after changing it");
	AssertFloatEqual(material.Specular(), 0.8f, eps, "specular should be 0.8 after changing it");
	AssertFloatEqual(material.Shininess(), 50.0f, eps, "shininess should be 50.0 after changing it");

	return 0;
}