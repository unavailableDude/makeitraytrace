#include <iostream>
#include <cmath>
#include <vector>

#include "../include/Ray.hpp"
#include "../include/Sphere.hpp"
#include "../include/Vec4.hpp"
#include "../include/RayHit.hpp"
#include "../include/Color4.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>


// ANSI color codes
#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"

using namespace MIRT;


bool CheckSphereInitialTransform(const Sphere& sphere, glm::mat4 expectedTransform) {
	return sphere.GetTransform() == expectedTransform;
}

bool CheckHitDistance(const RayHit& hit, float distance, float eps = Vec4::s_epsilon) {
	return std::abs(hit.T() - distance) < eps;
}

bool CheckHitDistanceOver(const RayHit& hit, float threshold) { return hit.T() > threshold; }

bool CheckNormalAtPoint(const Sphere& sphere,
                        const Vec4& point,
                        const Vec4& expectedNormal,
                        const std::string& title,
                        float eps = Vec4::s_epsilon) {
	if(IsVec4Equal(sphere.NormalAtPoint(point), expectedNormal, eps)) {
		std::cout << GREEN << "Passed! " << title << RESET << std::endl;
		return true;
	} else {
		std::cout << RED << "Failed! " << title << RESET << std::endl;
		std::cout << RED << "Expected: " << ToString(expectedNormal) << ", Got: " << ToString(sphere.NormalAtPoint(point))
		          << RESET << std::endl;
		return false;
	}
}

bool CheckMaterialEqual(const Material& mat1, const Material& mat2, float eps = Vec4::s_epsilon) {
	if((mat1.SurfaceColor() == mat2.SurfaceColor()) && std::abs(mat1.Ambient() - mat2.Ambient()) < eps &&
	   std::abs(mat1.Diffuse() - mat2.Diffuse()) < eps && std::abs(mat1.Specular() - mat2.Specular()) < eps &&
	   std::abs(mat1.Shininess() - mat2.Shininess()) < eps) {
		return true;
	}
	return false;
}

int main(int argc, char* argv[]) {
	Sphere sphere1 = Sphere();
	if(CheckSphereInitialTransform(sphere1, glm::identity<glm::mat4>())) {
		std::cout << GREEN << "Passed! " << "Sphere is initialized with correct transform." << RESET << std::endl;
	} else {
		std::cout << RED << "Failed! " << "Sphere is not initialized with correct transform." << RESET << std::endl;
	}

	// test that a default material has been created in a default sphere
	if(CheckMaterialEqual(sphere1.GetMaterial(), Material())) {
		std::cout << GREEN << "Passed! " << "Default material is created in a default sphere." << RESET << std::endl;
	} else {
		std::cout << RED << "Failed! " << "Default material is not created in a default sphere." << RESET << std::endl;
	}

	// this intersection should yield 2 points at (0, 0, -1) and (0, 0, 1), t1 = 4 & t2 = 6
	Ray ray1 = Ray(MakePoint(Vec4(0.0f, 0.0f, -5.0f)), MakeDir(Vec4(0.0f, 0.0f, 1.0f)));
	std::vector<RayHit> hits = sphere1.Intersect(ray1);
	if(CheckHitDistance(hits[0], 4.0f) && CheckHitDistance(hits[1], 6.0f)) {
		std::cout << GREEN << "Passed! " << "Ray intersects the sphere at the correct distance." << RESET << std::endl;
	} else {
		std::cout << RED << "Failed! " << "Ray does not intersect the sphere at the correct distance." << RESET << std::endl;
	}

	// this intersection should yield one point at (0, 1, 0)
	Ray ray2 = Ray(MakePoint(Vec4(0.0f, 1.0f, -5.0f)), MakeDir(Vec4(0.0f, 0.0f, 1.0f)));
	hits = sphere1.Intersect(ray2);
	if(CheckHitDistance(hits[0], 5.0f)) {
		std::cout << GREEN << "Passed! " << "Ray glances the sphere at the correct point." << RESET << std::endl;
	} else {
		std::cout << RED << "Failed! " << "Ray does not glances the sphere at the correct point." << RESET << std::endl;
	}

	// this intersection should yield no points, as the ray misses the sphere
	Ray ray3 = Ray(MakePoint(Vec4(2.0f, 2.0f, -5.0f)), MakeDir(Vec4(0.0f, 0.0f, 1.0f)));
	hits = sphere1.Intersect(ray3);
	if(hits.empty()) {
		std::cout << GREEN << "Passed! " << "Ray misses the sphere as expected." << RESET << std::endl;
	} else {
		std::cout << RED << "Failed! " << "Ray should not intersect the sphere." << RESET << std::endl;
	}

	// a ray inside the sphere still intersects at 2 points, t1 = -1, t2 = 1
	Ray ray4 = Ray(MakePoint(Vec4(0.0f, 0.0f, 0.0f)), MakeDir(Vec4(0.0f, 0.0f, 1.0f)));
	hits = sphere1.Intersect(ray4);
	if(CheckHitDistance(hits[0], -1.0f) && CheckHitDistance(hits[1], 1.0f)) {
		std::cout << GREEN << "Passed! "
		          << "a Ray that is inside the sphere should intersect at 2 points, with -t1, +t2" << RESET << std::endl;
	} else {
		std::cout << RED << "Failed! "
		          << "a Ray that is inside the sphere should intersect at 2 points, with -t1, +t2" << RESET << std::endl;
	}

	// a ray infront of the sphere should still have 2 hit behind it with the sphere, both t are negative, t1 = -6, t2 = -4
	Ray ray5 = Ray(MakePoint(Vec4(0.0f, 0.0f, 5.0f)), MakeDir(Vec4(0.0f, 0.0f, 1.0f)));
	hits = sphere1.Intersect(ray5);
	if(CheckHitDistance(hits[0], -6.0f) && CheckHitDistance(hits[1], -4.0f)) {
		std::cout << GREEN << "Passed! "
		          << "a Ray that is in front of the sphere should intersect at 2 points, both t are negative" << RESET
		          << std::endl;
	} else {
		std::cout << RED << "Failed! "
		          << "a Ray that is in front of the sphere should intersect at 2 points, both t are negative" << RESET
		          << std::endl;
	}

	// when transforming a sphere to (0, 1, 0), a ray ((0, 0, -3), (0, 0, 1)) should hit at (0, 1, 0)
	Ray ray6 = Ray(MakePoint(Vec4(0.0f, 0.0f, -3.0f)), MakeDir(Vec4(0.0f, 0.0f, 1.0f)));
	Sphere sphere2 = Sphere();
	sphere2.SetTransform(glm::translate(glm::identity<glm::mat4>(), glm::vec3(0.0f, 1.0f, 0.0f)));
	hits = sphere2.Intersect(ray6);
	if(CheckHitDistance(hits[0], 3.0f)) {
		std::cout << GREEN << "Passed! " << "Ray intersects the transformed sphere at the correct point." << RESET
		          << std::endl;
	} else {
		std::cout << RED << "Failed! " << "Ray does not intersect the transformed sphere at the correct point." << RESET
		          << std::endl;
	}

	// when the sphere is scaled by (2, 2, 2), the ray ((0, 0, -3), (0, 0, 1)) should hit at (-2, 0, 0) and (2, 0, 0)
	glm::mat4 scaling = glm::scale(glm::identity<glm::mat4>(), glm::vec3(2.0f, 2.0f, 2.0f));
	glm::mat4 transform = glm::transpose(scaling);// convert it to row-major
	sphere2.SetTransform(transform);
	hits = sphere2.Intersect(ray6);
	if(CheckHitDistance(hits[0], 1.0f) && CheckHitDistance(hits[1], 5.0f)) {
		std::cout << GREEN << "Passed! "
		          << "Ray intersects the scaled sphere at the correct points." << RESET << std::endl;
	} else {
		std::cout << RED << "Failed! "
		          << "Ray does not intersect the scaled sphere at the correct points, expected hit distances (1, 5), got ("
		          << hits[0].T() << ", " << hits[1].T() << ")" << RESET << std::endl;
	}

	// when the sphere is scaled by (2, 2, 2) then translated by (0, 2, 0),
	// the ray ((0, 0, -3), (0, 0, 1)) should hit at (0, 0, 0)
	glm::mat4 translation = glm::translate(glm::identity<glm::mat4>(), glm::vec3(0.0f, 2.0f, 0.0f));
	transform = glm::transpose(translation * scaling);// convert it to row-major
	sphere2.SetTransform(transform);
	hits = sphere2.Intersect(ray6);
	if(CheckHitDistance(hits[0], 3.0f)) {
		std::cout << GREEN << "Passed! "
		          << "Ray intersects the scaled and translated sphere at the correct point." << RESET << std::endl;
	} else {
		std::cout
		    << RED << "Failed! "
		    << "Ray does not intersect the scaled and translated sphere at the correct point, expected hit distances (3), got ("
		    << hits[0].T() << ")" << RESET << std::endl;
	}

	// the normals of a unit sphere at world origin
	Sphere sphere3 = Sphere();
	Vec4 point100 = MakePoint(Vec4(1.0f, 0.0f, 0.0f));
	Vec4 point010 = MakePoint(Vec4(0.0f, 1.0f, 0.0f));
	Vec4 point001 = MakePoint(Vec4(0.0f, 0.0f, 1.0f));
	CheckNormalAtPoint(sphere3, point100, Vec4(1.0f, 0.0f, 0.0f, 0.0f), "Normal of unit sphere at (1, 0, 0) is (1, 0, 0)");
	CheckNormalAtPoint(sphere3, point010, Vec4(0.0f, 1.0f, 0.0f, 0.0f), "Normal of unit sphere at (0, 1, 0) is (0, 1, 0)");
	CheckNormalAtPoint(sphere3, point001, Vec4(0.0f, 0.0f, 1.0f, 0.0f), "Normal of unit sphere at (0, 0, 1) is (0, 0, 1)");

	float sqrt3 = sqrt(3.0f);
	float thirdsqrt3 = sqrt3 / 3.0f;
	Vec4 normalSQRT3 = MakePoint(Vec4(thirdsqrt3, thirdsqrt3, thirdsqrt3));
	CheckNormalAtPoint(sphere3,
	                   normalSQRT3,
	                   Vec4(thirdsqrt3, thirdsqrt3, thirdsqrt3, 0.0f),
	                   "Normal of unit sphere at " + ToString(normalSQRT3) + " is " +
	                       ToString(Vec4(thirdsqrt3, thirdsqrt3, thirdsqrt3, 0.0f)));

	// normals of a unit sphere at (0, 1, 0)
	glm::mat4 translation3 = glm::translate(glm::identity<glm::mat4>(), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 transform3 = glm::transpose(translation3);
	sphere3.SetTransform(transform3);

	// note: not nesseserily on the surface, but it is on the intended direction
	// for example point110 and point011, normalizing them gives the point on the surface of the sphere, so the expected normal
	// given to CheckNormalAtPoint is normalized
	// TODO: clean up the naming scheme of the points
	Vec4 point110 = MakePoint(Vec4(1.0f, 1.0f, 0.0f));// point on the right of the sphere, n = (1, 0, 0)
	Vec4 point020 = MakePoint(Vec4(0.0f, 2.0f, 0.0f));// point on top of the sphere, n = (0, 1, 0)
	Vec4 point011 = MakePoint(Vec4(0.0f, 1.0f, 1.0f));// point on the front of the sphere, n = (0, 0, 1)
	CheckNormalAtPoint(sphere3,
	                   point110,
	                   Vec4(1.0f, 0.0f, 0.0f, 0.0f),
	                   "Normal of translated unit sphere(0, 1, 0) at (1, 1, 0) is " + ToString(Vec4(1.0f, 0.0f, 0.0f, 0.0f)));
	CheckNormalAtPoint(sphere3,
	                   point020,
	                   Vec4(0.0f, 1.0f, 0.0f, 0.0f),
	                   "Normal of translated unit sphere(0, 1, 0) at (0, 2, 0) is (0, 1, 0)");
	CheckNormalAtPoint(sphere3,
	                   point011,
	                   Vec4(0.0f, 0.0f, 1.0f, 0.0f),
	                   "Normal of translated unit sphere(0, 1, 0) at (0, 1, 1) is " + ToString(Vec4(0.0f, 0.0f, 1.0f, 0.0f)));

	// the normals of a scaled sphere
	glm::mat4 scaling2 = glm::scale(glm::identity<glm::mat4>(), glm::vec3(2.0f, 2.0f, 2.0f));
	glm::mat4 transform4 = glm::transpose(scaling2);
	sphere3.SetTransform(transform4);

	Vec4 pointS200 = MakePoint(Vec4(2.0f, 0.0f, 0.0f));
	Vec4 pointS020 = MakePoint(Vec4(0.0f, 2.0f, 0.0f));
	Vec4 pointS002 = MakePoint(Vec4(0.0f, 0.0f, 2.0f));
	CheckNormalAtPoint(sphere3, pointS200, Vec4(1.0f, 0.0f, 0.0f, 0.0f), "Normal of scaled sphere at (2, 0, 0) is (1, 0, 0)");
	CheckNormalAtPoint(sphere3, pointS020, Vec4(0.0f, 1.0f, 0.0f, 0.0f), "Normal of scaled sphere at (0, 2, 0) is (0, 1, 0)");
	CheckNormalAtPoint(sphere3, pointS002, Vec4(0.0f, 0.0f, 1.0f, 0.0f), "Normal of scaled sphere at (0, 0, 2) is (0, 0, 1)");

	// normals of a scaled translated sphere, at (0, 1, 0) scaled by 2
	Sphere sphere4 = Sphere();
	glm::mat4 translation4 = glm::translate(glm::identity<glm::mat4>(), glm::vec3(0.0f, 1.0f, 0.0f));
	scaling2 = glm::scale(glm::identity<glm::mat4>(), glm::vec3(2.0f, 2.0f, 2.0f));
	glm::mat4 transform5 = glm::transpose(translation4 * scaling2);
	sphere4.SetTransform(transform5);

	Vec4 pointSphere4Up = MakePoint(Vec4(0.0f, 3.0f, 0.0f));
	Vec4 pointSphere4LeftBottom = MakePoint(Vec4(-2.0f, 0.0f, 0.0f));
	Vec4 pointSphere4Left = MakePoint(Vec4(-2.0f, 1.0f, 0.0f));
	CheckNormalAtPoint(sphere4,
	                   pointSphere4Up,
	                   Vec4(0.0f, 1.0f, 0.0f, 0.0f),
	                   "Normal of scaled translated sphere at (0, 3, 0) is (0, 1, 0)");
	CheckNormalAtPoint(sphere4,
	                   pointSphere4LeftBottom,
	                   Vec4(-(2.0f / sqrt(5.0f)), -(1.0f / sqrt(5.0f)), 0.0f, 0.0f),
	                   "Normal of scaled translated sphere at (-2, 0, 0) is (-2/sqrt(5), -1/sqrt(5), 0)");

	CheckNormalAtPoint(sphere4,
	                   pointSphere4Left,
	                   Vec4(-1.0f, 0.0f, 0.0f, 0.0f),
	                   "Normal of scaled translated sphere at (-2, 1, 0) is (-1, 0, 0)");

	// normals of a scaled translated sphere at (2, 2, 0) scaled by 2
	glm::mat4 translation5 = glm::translate(glm::identity<glm::mat4>(), glm::vec3(2.0f, 2.0f, 0.0f));
	glm::mat4 transform6 = glm::transpose(translation5 * scaling2);
	sphere4.SetTransform(transform6);

	Vec4 pointS3010 = MakePoint(Vec4(0.0f, 2.0f, 0.0f));
	Vec4 pointLeftLowerMid = MakePoint(Vec4(2.0f - (2.0f * sqrt(2.0f)), 2.0f - (2.0f * sqrt(2.0f)), 0.0f));
	CheckNormalAtPoint(sphere4,
	                   pointS3010,
	                   Vec4(-1.0f, 0.0f, 0.0f, 0.0f),
	                   "Normal of sphere(2, 2, 0) scaled by 2 at point(0, 2, 0) is (-1, 0, 0)");
	CheckNormalAtPoint(sphere4,
	                   pointLeftLowerMid,
	                   Vec4(-1.0f, -1.0f, 0.0f, 0.0f).Normalize(),
	                   "Normal of sphere(2, 2, 0) scaled by 2 at point(1, 1, 0) is (-sqrt(2), -sqrt(2), 0)");

	return 0;
}
