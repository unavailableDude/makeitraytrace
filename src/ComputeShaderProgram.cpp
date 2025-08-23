#include "CommonMacros.hpp"

#include "ComputeShaderProgram.hpp"
#include "glm/glm.hpp"


namespace MIRT {

// public:
ComputeShaderProgram::ComputeShaderProgram() : _programID{}, _shaderSrcPath{""}, _isShaderReady{false} {}

ComputeShaderProgram::ComputeShaderProgram(const std::string& shaderSrcPath)
    : _programID{},
      _shaderSrcPath{shaderSrcPath},
      _isShaderReady{false} {}

ComputeShaderProgram::~ComputeShaderProgram() { GLCALL(glDeleteProgram(_programID)); }

void ComputeShaderProgram::Use() { GLCALL(glUseProgram(_programID)); }
GLuint ComputeShaderProgram::GetProgram() { return _programID; }

void ComputeShaderProgram::SetUniform1f(const std::string& name, float value) {
	GLint location = glGetUniformLocation(_programID, name.c_str());
	glUniform1f(location, value);
}
void ComputeShaderProgram::SetUniform1i(const std::string& name, int value) {
	GLint location = glGetUniformLocation(_programID, name.c_str());
	glUniform1i(location, value);
}
void ComputeShaderProgram::SetUniform2f(const std::string& name, const Vec4& value) {
	GLint location = glGetUniformLocation(_programID, name.c_str());
	glUniform2f(location, value._x, value._y);
}

void ComputeShaderProgram::LogInfo() {
	std::cout << "-------- Shader Program Info --------" << std::endl;
	std::cout << "GLuint program:       " << _programID << std::endl;
	std::cout << "shader path:         " << _shaderSrcPath << std::endl;
	std::cout << "-------- ------ ------- ---- --------" << std::endl;
}

void ComputeShaderProgram::ReloadShader(const std::string& shaderSrcPath) {
	_isShaderReady = false;
	GLCALL(glDeleteProgram(_programID));
	_programID = CreateShader(shaderSrcPath);
	_isShaderReady = true;
}

void ComputeShaderProgram::cookThatShader() {
	GLCALL(glDeleteProgram(_programID));
	_programID = CreateShader(_shaderSrcPath);
	_isShaderReady = true;
}

bool ComputeShaderProgram::IsShaderReady() { return _isShaderReady; }

// private:
GLuint ComputeShaderProgram::CompileShader(GLenum shaderType, const std::string& shaderSrc) {
	GLuint shaderObject;

	// for now the compute shader is separate! please don't forget it
	if(shaderType == GL_COMPUTE_SHADER) {
		shaderObject = glCreateShader(GL_COMPUTE_SHADER);
	} else {
		std::cerr << "ERROR::SHADER::UNSUPPORTED_TYPE\n";
		return 0;
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
GLuint ComputeShaderProgram::CreateShader(const std::string& shaderSrcPath) {
	GLuint programObject = glCreateProgram();
	// make shaders
	ShaderLoader shaderLoader;
	GLuint shader = CompileShader(GL_COMPUTE_SHADER, shaderLoader.LoadShaderFromFile(shaderSrcPath));

	// attach shaders to program
	glAttachShader(programObject, shader);
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
	GLCALL(glDeleteShader(shader));

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