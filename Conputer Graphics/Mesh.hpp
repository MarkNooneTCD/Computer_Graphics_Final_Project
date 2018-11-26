#pragma once
#include "Constants.hpp"

class Mesh {
public:
	ModelData mesh_data;

	Mesh(const char* fn, unsigned int vao, GLuint spID);
	Mesh();

	void generateObjectBufferMesh();
	mat4 getModel();
	void scaleModel(vec3 scaleMat);
	void translateModel(vec3 translateMat);
	void setRotation(int rot);
	glm::vec3 getModelCoord();

private:
	mat4 model;
	mat4 modelRot;
	mat4 modelScale;
	mat4 modelTrans;
	int currentRot;
	const char* file_name;
	GLuint shaderProgramID;
	GLuint loc1, loc2, loc3;
	unsigned int vao;

	void setInnerRotation();
	ModelData load_mesh(const char* file_name);
};



