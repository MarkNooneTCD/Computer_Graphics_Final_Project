#pragma once
#include "Game.hpp"

GLuint shaderProgramID;
std::unordered_map<std::string, Mesh> meshes;
GLfloat rotate_y = 0.0f;
unsigned int mesh_vao = 0;
mat4 modelTrans = identity_mat4();

void display() {

	// tell GL to only draw onto a pixel if the shape is closer to the viewer
	glEnable(GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"
	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shaderProgramID);


	//Declare your uniform variables that will be used in your shader
	int matrix_location = glGetUniformLocation(shaderProgramID, "model");
	int view_mat_location = glGetUniformLocation(shaderProgramID, "view");
	int proj_mat_location = glGetUniformLocation(shaderProgramID, "proj");

	// --------------------------------------------------------------------------
	// -----------------------  Root of the Hierarchy  --------------------------
	// --------------------------------------------------------------------------
	glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, -20.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 perspective = glm::perspective(45.0f, (float)Constants::width / (float)Constants::height, 0.1f, 100.0f);
	mat4 model = identity_mat4();
	mat4 modelRot = identity_mat4();
	mat4 modelScale = identity_mat4();
	mat4 modelTrans = identity_mat4();
	modelRot = rotate_z_deg(modelRot, rotate_y);
	modelScale = scale(modelScale, vec3(0.1f, 0.1f, 0.1f));
	model = modelTrans * (modelRot * (modelScale * model));

	// update uniforms & draw
	glUniformMatrix4fv(proj_mat_location, 1, GL_FALSE, glm::value_ptr(perspective));
	glUniformMatrix4fv(view_mat_location, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, model.m);
	glDrawArrays(GL_TRIANGLES, 0, meshes["toilet"].mesh_data.mPointCount);

	// --------------------------------------------------------------------------
	// -----------------------  Children Hierarchy(1)  --------------------------
	// --------------------------------------------------------------------------
	// Set up the child matrix1
	mat4 modelChild10 = identity_mat4();
	modelChild10 = rotate_y_deg(modelChild10, rotate_y);
	modelChild10 = translate(modelChild10, vec3(0.0f, 40.0f, 0.0f));

	// Set up the child matrix2
	mat4 modelChild11 = identity_mat4();
	modelChild11 = rotate_y_deg(modelChild11, rotate_y);
	modelChild11 = translate(modelChild11, vec3(0.0f, -40.0f, 0.0f));

	// Apply the root matrix to the child matrix
	modelChild10 = model * modelChild10;
	modelChild11 = model * modelChild11;

	// Update the appropriate uniform and draw the mesh again for both children
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, modelChild10.m);
	glDrawArrays(GL_TRIANGLES, 0, meshes["toilet"].mesh_data.mPointCount);

	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, modelChild11.m);
	glDrawArrays(GL_TRIANGLES, 0, meshes["toilet"].mesh_data.mPointCount);

	// --------------------------------------------------------------------------
	// -------------------  Children Hierarchy(2.1 / 2.2)  ----------------------
	// --------------------------------------------------------------------------

	mat4 modelChild21 = identity_mat4();
	modelChild21 = translate(modelChild21, vec3(40.0f, 0.0f, 0.0f));
	modelChild21 = modelChild11 * modelChild21;

	mat4 modelChild22 = identity_mat4();
	modelChild22 = translate(modelChild22, vec3(40.0f, 0.0f, 0.0f));
	modelChild22 = modelChild21 * modelChild22;

	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, modelChild21.m);
	glDrawArrays(GL_TRIANGLES, 0, meshes["toilet"].mesh_data.mPointCount);

	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, modelChild22.m);
	glDrawArrays(GL_TRIANGLES, 0, meshes["toilet"].mesh_data.mPointCount);

	// --------------------------------------------------------------------------
	// -------------------  Children Hierarchy(3.1 / 3.2)  ----------------------
	// --------------------------------------------------------------------------

	mat4 modelChild31 = identity_mat4();
	modelChild31 = translate(modelChild31, vec3(-40.0f, 0.0f, 0.0f));
	modelChild31 = modelChild10 * modelChild31;

	mat4 modelChild32 = identity_mat4();
	modelChild32 = translate(modelChild32, vec3(-40.0f, 0.0f, 0.0f));
	modelChild32 = modelChild31 * modelChild32;

	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, modelChild31.m);
	glDrawArrays(GL_TRIANGLES, 0, meshes["toilet"].mesh_data.mPointCount);

	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, modelChild32.m);
	glDrawArrays(GL_TRIANGLES, 0, meshes["toilet"].mesh_data.mPointCount);

	glutSwapBuffers();
}


void updateScene() {

	static DWORD last_time = 0;
	DWORD curr_time = timeGetTime();
	if (last_time == 0)
		last_time = curr_time;
	float delta = (curr_time - last_time) * 0.001f;
	last_time = curr_time;

	// Rotate the model slowly around the y axis at 20 degrees per second
	rotate_y += 20.0f * delta;
	rotate_y = fmodf(rotate_y, 360.0f);

	// Draw the next frame
	glutPostRedisplay();
}


void init()
{
	// Setup Shader
	shaderProgramID = CompileShaders();

	// load mesh into a vertex buffer array
	meshes["toilet"] = Mesh("toilet.obj", shaderProgramID);
	meshes["toilet"].generateObjectBufferMesh();
}

// Placeholder code for the keypress
void keypress(int key, int x, int y) {

	glutPostRedisplay();
}