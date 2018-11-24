#pragma once
#include "Constants.hpp"

//class Shader {
//public:
//	Shader();
//	GLuint CompileShaders();
//	void UseShader();
//	GLuint getShaderProgramId();
//private:
//	GLuint shaderProgramID;
//	char* readShaderSource(const char* shaderFile);
//	void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
//};

GLuint CompileShaders();
static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
char* readShaderSource(const char* shaderFile);
