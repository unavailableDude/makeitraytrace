#include <iostream>
#include <cassert>
#include <cmath>

#include "../include/Vec4.hpp"
using namespace RTCE;

// ANSI color codes
#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"


// returns true for equal, takes epsilon into account
bool AssertEqual(const Vec4& a, float x, float y, float z, float w, float eps, const char* title = "") {
	if((fabs(a._x - x) < eps) && (fabs(a._y - y) < eps) && (fabs(a._z - z) < eps) && (fabs(a._w - w) < eps)) {
		std::cout << GREEN << "passed! " << title << RESET << std::endl;
		return true;
	}
	std::cerr << RED << "failed! " << title << " Expected: (" << x << ", " << y << ", " << z << ", " << w << "), Got: ("
	          << a._x << ", " << a._y << ", " << a._z << ", " << a._w << ")" << RESET << std::endl;
	return false;
}

bool AssertFloatEqual(float a, float b, float eps, const char* title = "") {
	if(fabs(a - b) < eps) {
		std::cout << GREEN << "passed! " << title << RESET << std::endl;
		return true;
	}
	std::cerr << RED << "failed! " << title << " Expected: " << b << ", Got: " << a << RESET << std::endl;
	return false;
}

int main(int argc, char* argv[]) {
	Vec4 a1 = Vec4(4.3f, -4.2f, 3.1f, 1.0f);
	Vec4 a2 = Vec4(-2.4f, 1.09f, 1.0f, 0.0f);
	Vec4 point1 = MakePoint(Vec4(4.0f, -4.0f, 3.0f));
	Vec4 point2 = MakePoint(Vec4(1.0f, 2.0f, -1.0f));
	Vec4 dir1 = MakeDir(Vec4(4.0f, -4.0f, 3.0f));
	Vec4 dir2 = MakeDir(Vec4(1.5f, 2.2f, -1.0f));

	float eps = Vec4::epsilon;// epsilon for floating point comparisons

	// calling Vec4 gives correct values
	AssertEqual(a1, 4.3f, -4.2f, 3.1f, 1.0f, eps, "Vec4 Initialization");

	// MakePoint and MakeDir return correct values
	AssertEqual(point1, 4.0f, -4.0f, 3.0f, 1.0f, eps, "Vec4 MakePoint returns vec4 with w = 1");
	AssertEqual(dir1, 4.0f, -4.0f, 3.0f, 0.0f, eps, "Vec4 MakeDir returns vec4 with w = 0");

	// addition and subtraction work correctly
	Vec4 sum = a1 + a2;
	AssertEqual(sum, 1.9f, -3.11f, 4.1f, 1.0f, eps, "Vec4 addition adds all components");
	Vec4 diff = a1 - a2;
	AssertEqual(diff, 6.7f, -5.29f, 2.1f, 1.0f, eps, "Vec4 subtraction subtracts all components");

	// subbing 2 points gives a direction (w = 0)
	Vec4 dirFromPoints = point1 - point2;
	AssertEqual(dirFromPoints, 3.0f, -6.0f, 4.0f, 0.0f, eps, "Vec4 point - point gives a direction");

	// subbing a vector from a point gives a point
	Vec4 pointFromVec = point1 - dir2;
	AssertEqual(pointFromVec, 2.5f, -6.2f, 4.0f, 1.0f, eps, "Vec4 point - vector gives a point");

	// subbing 2 vectors gives a vector
	Vec4 vecFromVecs = a1 - a2;
	AssertEqual(vecFromVecs, 6.7f, -5.29f, 2.1f, 1.0f, eps, "Vec4 vector - vector gives a vector");

	// subbing a point from a vector is nonsense (w = -1)
	Vec4 nonsense = dir1 - point1;
	AssertEqual(nonsense, 0.0f, 0.0f, 0.0f, -1.0f, eps, "Vec4 vector - point gives nonsense (w = -1)");

	// negating a vector negates all components
	Vec4 negated = -a1;
	AssertEqual(negated, -4.3f, 4.2f, -3.1f, -1.0f, eps, "Vec4 negating a vector negates all components");

	// multiplying by a scalar scales all components
	Vec4 scaledUp = a1 * 3.5f;
	Vec4 scaledDown = a1 * 0.5f;
	AssertEqual(scaledUp, 15.05f, -14.7f, 10.85f, 3.5f, eps, "Vec4 scaling up by a scalar scales all components");
	AssertEqual(scaledDown, 2.15f, -2.1f, 1.55f, 0.5f, eps, "Vec4 scaling down by a scalar scales all components");

	// dividing by a scalar divides all components
	Vec4 divided = a1 / 2.0f;
	AssertEqual(divided, 2.15f, -2.1f, 1.55f, 0.5f, eps, "Vec4 division by a scalar divides all components");

	// dividing by zero gives a vector with all components zero ( may change )
	Vec4 dividedByZero = a1 / 0.0f;
	AssertEqual(dividedByZero, 0.0f, 0.0f, 0.0f, 0.0f, eps, "Vec4 division by zero gives zero vector");

	// magnitude of unit vectors is 1
	Vec4 unitVecX = MakeDir(Vec4(1.0f, 0.0f, 0.0f));
	Vec4 unitVecY = MakeDir(Vec4(0.0f, 1.0f, 0.0f));
	Vec4 unitVecZ = MakeDir(Vec4(0.0f, 0.0f, 1.0f));
	// magnitude of x = 1 is 1
	AssertFloatEqual(unitVecX.Magnitude(), 1.0f, eps, "Vec4 unit vector x has magnitude 1");
	// magnitude of y = 1 is 1
	AssertFloatEqual(unitVecY.Magnitude(), 1.0f, eps, "Vec4 unit vector y has magnitude 1");
	// magnitude of z = 1 is 1
	AssertFloatEqual(unitVecZ.Magnitude(), 1.0f, eps, "Vec4 unit vector z has magnitude 1");

	// magnitude of 1,2,3 is sqrt(14)
	Vec4 vec14 = MakeDir(Vec4(1.0f, 2.0f, 3.0f));
	AssertFloatEqual(vec14.Magnitude(), sqrtf(14.0f), eps, "Vec4 vector (1,2,3) has magnitude sqrt(14)");

	// magnitude of -1,-2,-3 is sqrt(14)
	Vec4 negVec14 = MakeDir(Vec4(-1.0f, -2.0f, -3.0f));
	AssertFloatEqual(negVec14.Magnitude(), sqrtf(14.0f), eps, "Vec4 vector (-1,-2,-3) has magnitude sqrt(14)");

	// magnitude of 0,0,0 is 0
	Vec4 zeroVec = MakeDir(Vec4(0.0f, 0.0f, 0.0f));
	AssertFloatEqual(zeroVec.Magnitude(), 0.0f, eps, "Vec4 zero vector has magnitude 0");

	return 0;
}