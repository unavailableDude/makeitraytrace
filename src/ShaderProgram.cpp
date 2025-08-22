#include "CommonMacros.hpp"

#include "ShaderProgram.hpp"
#include "glm/glm.hpp"


namespace MIRT {

// public:
ShaderProgram::ShaderProgram() : _programID{}, _vShaderSrcPath{""}, _fShaderSrcPath{""}, _isShaderReady{false} {}

ShaderProgram::ShaderProgram(const std::string& vShaderSrcPath, const std::string& fShaderSrcPath)
    : _programID{},
      _vShaderSrcPath{vShaderSrcPath},
      _fShaderSrcPath{fShaderSrcPath},
      _isShaderReady{false} {}

ShaderProgram::~ShaderProgram() { GLCALL(glDeleteProgram(_programID)); }

void ShaderProgram::Use() { GLCALL(glUseProgram(_programID)); }
GLuint ShaderProgram::GetProgram() { return _programID; }

void ShaderProgram::SetUniform1f(const std::string& name, float value) {
	GLint location = glGetUniformLocation(_programID, name.c_str());
	glUniform1f(location, value);
}
void ShaderProgram::SetUniform1i(const std::string& name, int value) {
	GLint location = glGetUniformLocation(_programID, name.c_str());
	glUniform1i(location, value);
}
void ShaderProgram::SetUniform2f(const std::string& name, const Vec4& value) {
	GLint location = glGetUniformLocation(_programID, name.c_str());
	glUniform2f(location, value._x, value._y);
}

void ShaderProgram::LogInfo() {
	std::cout << "-------- Shader Program Info --------" << std::endl;
	std::cout << "GLuint program:       " << _programID << std::endl;
	std::cout << "vertex shader path:   " << _vShaderSrcPath << std::endl;
	std::cout << "fragment shader path: " << _fShaderSrcPath << std::endl;
	std::cout << "-------- ------ ------- ---- --------" << std::endl;
}

void ShaderProgram::ReloadShader(const std::string& vShaderSrcPath, const std::string& fShaderSrcPath) {
	_isShaderReady = false;
	GLCALL(glDeleteProgram(_programID));
	_programID = CreateShader(vShaderSrcPath, fShaderSrcPath);
	_isShaderReady = true;
}

void ShaderProgram::cookThatShader() {
	GLCALL(glDeleteProgram(_programID));
	_programID = CreateShader(_vShaderSrcPath, _fShaderSrcPath);
	_isShaderReady = true;
}

bool ShaderProgram::IsShaderReady() { return _isShaderReady; }

// private:
GLuint ShaderProgram::CompileShader(GLenum shaderType, const std::string& shaderSrc) {
	GLuint shaderObject;

	if(shaderType == GL_VERTEX_SHADER) {
		shaderObject = glCreateShader(GL_VERTEX_SHADER);

	} else if(shaderType == GL_FRAGMENT_SHADER) {
		shaderObject = glCreateShader(GL_FRAGMENT_SHADER);
	}
	const char* src = shaderSrc.c_str();
	GLCALL(glShaderSource(shaderObject, 1, &src, nullptr));
	GLCALL(glCompileShader(shaderObject));

	GLint success;
	glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &success);
	if(!success) {
		char infoLog[512];
		glGetShaderInfoLog(shaderObject, 512, nullptr, infoLog);
		std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return shaderObject;
}
GLuint ShaderProgram::CreateShader(const std::string& vShaderSrcPath, const std::string& fShaderSrcPath) {
	GLuint programObject = glCreateProgram();
	// make shaders
	ShaderLoader shaderLoader;
	GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, shaderLoader.LoadShaderFromFile(vShaderSrcPath));
	GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, shaderLoader.LoadShaderFromFile(fShaderSrcPath));
	// attach shaders to program
	glAttachShader(programObject, vertexShader);
	glAttachShader(programObject, fragmentShader);
	glLinkProgram(programObject);

	// check for errors
	GLint success;
	glGetProgramiv(programObject, GL_LINK_STATUS, &success);
	if(!success) {
		char infoLog[512];
		glGetProgramInfoLog(programObject, 512, nullptr, infoLog);
		std::cerr << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	// delete shaders
	GLCALL(glDeleteShader(vertexShader));
	GLCALL(glDeleteShader(fragmentShader));

	glValidateProgram(programObject);
	GLint validateStatus;
	glGetProgramiv(programObject, GL_VALIDATE_STATUS, &validateStatus);
	if(!validateStatus) {
		char infoLog[512];
		glGetProgramInfoLog(programObject, 512, nullptr, infoLog);
		std::cerr << "ERROR::PROGRAM::VALIDATION_FAILED\n" << infoLog << std::endl;
	}

	return programObject;
}

}// namespace MIRT