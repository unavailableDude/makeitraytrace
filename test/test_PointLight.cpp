#include <iostream>


#include "PointLight.hpp"


// ANSI color codes
#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"


using namespace MIRT;


int main(int argc, char* argv[]) {
	PointLight light;

	if(light.GetIntensity() == Color4(1.0f, 1.0f, 1.0f, 1.0f)) {
		std::cout << GREEN << "Point Light initialized with Color4(1, 1, 1, 1)" << RESET << std::endl;
	} else
		std::cout << RED << "Point Light not initialized with Color4(1, 1, 1, 1), got " << ToString(light.GetIntensity())
		          << RESET << std::endl;

	if(light.GetPosition() == Vec4(0.0f, 0.0f, 0.0f, 1.0f)) {
		std::cout << GREEN << "Point Light initialized with Vec4(0, 0, 0, 1)" << RESET << std::endl;
	} else
		std::cout << RED << "Point Light not initialized with Vec4(0, 0, 0, 1), got " << ToString(light.GetPosition()) << RESET
		          << std::endl;

	return 0;
}