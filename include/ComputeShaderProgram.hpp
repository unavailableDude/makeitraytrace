#pragma once

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "ShaderLoader.hpp"
#include "Vec4.hpp"

#include <iostream>


namespace MIRT {


class ComputeShaderProgram {
public:
	ComputeShaderProgram();
	ComputeShaderProgram(const std::string& shaderSrcPath);
	~ComputeShaderProgram();

	void Use();
	GLuint GetProgram();

	void SetUniform1f(const std::string& name, float value);
	void SetUniform1i(const std::string& name, int value);
	void SetUniform2f(const std::string& name, const Vec4& value);
	void SetUniform4f(const std::string& name, const Vec4& value);

	void LogInfo();
	void ReloadShader(const std::string& shaderSrcPath);
	void cookThatShader();
	bool IsShaderReady();

private:
	GLuint CompileShader(GLenum shaderType, const std::string& shaderSrc);
	GLuint CreateShader(const std::string& shaderSrc);

	// private:
	GLuint _programID;
	std::string _shaderSrcPath;
	bool _isShaderReady;
};

}// namespace MIRT