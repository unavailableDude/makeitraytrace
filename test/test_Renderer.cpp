#include "../include/Renderer.hpp"

#include <cstdint>
#include <iostream>


using namespace MIRT;

// ANSI color codes
#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"


bool CheckDimensions(const Renderer& r,
                     uint16_t expectedWidth,
                     uint16_t expectedHeight,
                     const char* title = "",
                     bool print = true) {
	if(r.GetWidth() == expectedWidth && r.GetHeight() == expectedHeight) {
		if(print) std::cout << GREEN << "passed! " << title << RESET << std::endl;
		return true;
	} else {
		if(print)
			std::cerr << RED << "failed! " << title << " Expected dimensions: (" << expectedWidth << ", " << expectedHeight
			          << "), got: (" << r.GetWidth() << ", " << r.GetHeight() << ")" << RESET << std::endl;
		return false;
	}
}


int main(int argc, char* argv[]) {
	// renderer is created with the specified dimensions
	Renderer rend1 = Renderer(20, 10);
	CheckDimensions(rend1, 20, 10, "Renderer creation with specified dimensions.");

	return 0;
}