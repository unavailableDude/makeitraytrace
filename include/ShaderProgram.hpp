#pragma once

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "ShaderLoader.hpp"
#include "Vec4.hpp"

#include <iostream>


namespace MIRT {


class ShaderProgram {
public:
	ShaderProgram();
	ShaderProgram(const std::string& vShaderSrcPath, const std::string& fShaderSrcPath);
	~ShaderProgram();

	void Use();
	GLuint GetProgram();

	void SetUniform1f(const std::string& name, float value);
	void SetUniform1i(const std::string& name, int value);
	void SetUniform2f(const std::string& name, const Vec4& value);
	void SetUniform4f(const std::string& name, const Vec4& value);

	void LogInfo();
	void ReloadShader(const std::string& vShaderSrcPath, const std::string& fShaderSrcPath);
	void cookThatShader();
	bool IsShaderReady();

private:
	GLuint CompileShader(GLenum shaderType, const std::string& shaderSrc);
	GLuint CreateShader(const std::string& vShaderSrc, const std::string& fShaderSrc);

	// private:
	GLuint _programID;
	std::string _vShaderSrcPath;
	std::string _fShaderSrcPath;
	bool _isShaderReady;
};

}// namespace MIRT