#pragma once
#include "Constants.hpp"

class MyRectangle {
public:
	GLfloat* colors;
	GLfloat* vertices;
	MyRectangle(GLfloat vertices[], GLfloat colours[], GLuint numVertices);
	MyRectangle();
	GLuint generateObjectBuffer();
	void linkBufferToShader(GLuint shaderProgramID);
private: 
	GLuint numVertices;
};