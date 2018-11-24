#pragma once
#include "Constants.hpp"

class Mesh {
public:
	ModelData mesh_data;

	Mesh(const char* fn, GLuint spID);
	Mesh();

	void generateObjectBufferMesh();

private:
	const char* file_name;
	GLuint shaderProgramID;
	GLuint loc1, loc2, loc3;

	ModelData load_mesh(const char* file_name);
};