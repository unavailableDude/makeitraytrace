#pragma once
#include <string>
#include <fstream>


class ShaderLoader {
public:
	static std::string LoadShaderFromFile(const std::string& filename);
};