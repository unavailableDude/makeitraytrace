#include <../include/ShaderLoader.hpp>
#include <iostream>


std::string ShaderLoader::LoadShaderFromFile(const std::string& filename) {
	std::string resultString = "";

	std::string currLine = "";
	std::ifstream fileStream{filename.c_str()};
	if(fileStream.is_open()) {
		while(std::getline(fileStream, currLine)) {
			resultString += currLine + "\n";
		}
		fileStream.close();
	} else {
		std::cout << "Failed to open file: " << filename << std::endl;
	}
	return resultString;
}