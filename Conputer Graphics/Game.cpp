#pragma once
#include "Game.hpp"

GLuint phongProgramID, skyboxProgramID;
std::unordered_map<std::string, Mesh> meshes;
GLfloat rotate_y = 0.0f;
GLuint VAOS[10];
mat4 modelTrans = identity_mat4();
MyRectangle ground_plane;
float zoom = 16.0f;
float camera_alpha = 260.0f;
unsigned int skyboxVAO, skyboxVBO;
unsigned int cubemapTexture;

float skyboxVertices[] = {
	// positions          
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f
};

void display() {

	// tell GL to only draw onto a pixel if the shape is closer to the viewer
	glEnable(GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"
	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(phongProgramID);

	//Declare your uniform variables that will be used in your shader
	int matrix_location = glGetUniformLocation(phongProgramID, "model");
	int view_mat_location = glGetUniformLocation(phongProgramID, "view");
	int proj_mat_location = glGetUniformLocation(phongProgramID, "proj");

	glm::mat4 view = glm::lookAt((meshes["gino"].getModelCoord() + glm::vec3((0.0f + (zoom*cos(camera_alpha * (M_PI /180)))), zoom, (0.0f + (zoom*sin(camera_alpha * (M_PI / 180))) ))),
		 meshes["gino"].getModelCoord(),
		glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 perspective = glm::perspective(45.0f, (float)Constants::game_width / (float)Constants::game_height, 0.1f, 100.0f);

	// update uniforms & draw
	glUniformMatrix4fv(proj_mat_location, 1, GL_FALSE, glm::value_ptr(perspective));
	glUniformMatrix4fv(view_mat_location, 1, GL_FALSE, glm::value_ptr(view));

	glBindVertexArray(VAOS[0]);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, meshes["carrot"].getModel().m);
	glDrawArrays(GL_TRIANGLES, 0, meshes["carrot"].mesh_data.mPointCount);

	glBindVertexArray(VAOS[1]);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, meshes["crystal"].getModel().m);
	glDrawArrays(GL_TRIANGLES, 0, meshes["crystal"].mesh_data.mPointCount);

	glBindVertexArray(VAOS[2]);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, meshes["floor"].getModel().m);
	glDrawArrays(GL_TRIANGLES, 0, meshes["floor"].mesh_data.mPointCount);

	glBindVertexArray(VAOS[3]);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, meshes["gino"].getModel().m);
	glDrawArrays(GL_TRIANGLES, 0, meshes["gino"].mesh_data.mPointCount);

	glBindVertexArray(VAOS[4]);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, meshes["car"].getModel().m);
	glDrawArrays(GL_TRIANGLES, 0, meshes["car"].mesh_data.mPointCount);
	
	// Setup animated Car
	glBindVertexArray(VAOS[5]);
	meshes["wheel1"].setTransMat(vec3(meshes["car"].getModelCoord()[0] + 1.8f, meshes["car"].getModelCoord()[1] + -0.2f, meshes["car"].getModelCoord()[2] + 1.6f));
	meshes["wheel1"].rotate_z_axis(1.0f);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, meshes["wheel1"].getModel().m);
	glDrawArrays(GL_TRIANGLES, 0, meshes["wheel1"].mesh_data.mPointCount);
	
	glBindVertexArray(VAOS[6]);
	meshes["wheel2"].setTransMat(vec3(meshes["car"].getModelCoord()[0] + 2.3f, meshes["car"].getModelCoord()[1] + -0.2f, meshes["car"].getModelCoord()[2] -2.4f));
	meshes["wheel2"].rotate_z_axis(1.0f);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, meshes["wheel2"].getModel().m);
	glDrawArrays(GL_TRIANGLES, 0, meshes["wheel2"].mesh_data.mPointCount);
	
	glBindVertexArray(VAOS[7]);
	meshes["wheel3"].setTransMat(vec3(meshes["car"].getModelCoord()[0] - 1.8f, meshes["car"].getModelCoord()[1] + -0.2f, meshes["car"].getModelCoord()[2] + 1.5f));
	meshes["wheel3"].rotate_z_axis(1.0f);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, meshes["wheel3"].getModel().m);
	glDrawArrays(GL_TRIANGLES, 0, meshes["wheel3"].mesh_data.mPointCount);

	glBindVertexArray(VAOS[8]);
	meshes["wheel4"].setTransMat(vec3(meshes["car"].getModelCoord()[0] - 1.4f, meshes["car"].getModelCoord()[1] + -0.2f, meshes["car"].getModelCoord()[2] - 2.4f));
	meshes["wheel4"].rotate_z_axis(1.0f);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, meshes["wheel4"].getModel().m);
	glDrawArrays(GL_TRIANGLES, 0, meshes["wheel4"].mesh_data.mPointCount);

	// Sky map
	glDepthFunc(GL_LEQUAL);
	glUseProgram(skyboxProgramID);
	mat4 sky = identity_mat4();
	glBindVertexArray(skyboxVAO);
	int sky_proj_location = glGetUniformLocation(skyboxProgramID, "projection");
	int sky_view_location = glGetUniformLocation(skyboxProgramID, "view");
	glUniformMatrix4fv(sky_proj_location, 1, GL_FALSE, glm::value_ptr(perspective));
	glUniformMatrix4fv(sky_view_location, 1, GL_FALSE, sky.m);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS);

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
	skyboxProgramID = CompileShaders("../Shaders/skyboxVertexShader.txt", "../Shaders/skyboxFragmentShader.txt");
	glUseProgram(skyboxProgramID);

	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	GLuint apos = glGetAttribLocation(skyboxProgramID, "aPos");
	glEnableVertexAttribArray(apos);
	glVertexAttribPointer(apos, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	// load textures
   // -------------
	std::vector<std::string> faces
	{
		"C:\\Users\\Mark Noone\\Desktop\\Conputer Graphics\\Textures\\white.jpeg",
		"C:\\Users\\Mark Noone\\Desktop\\Conputer Graphics\\Textures\\white.jpeg",
		"C:\\Users\\Mark Noone\\Desktop\\Conputer Graphics\\Textures\\white.jpeg",
		"C:\\Users\\Mark Noone\\Desktop\\Conputer Graphics\\Textures\\white.jpeg",
		"C:\\Users\\Mark Noone\\Desktop\\Conputer Graphics\\Textures\\white.jpeg",
		"C:\\Users\\Mark Noone\\Desktop\\Conputer Graphics\\Textures\\white.jpeg"
	};
	cubemapTexture = loadCubemap(faces);

	glUniform1i(glGetUniformLocation(skyboxProgramID, "skybox"), 0);
	glGenVertexArrays(10, VAOS);

	phongProgramID = CompileShaders("../Shaders/phongVertexShader.txt", "../Shaders/phongFragmentShader.txt");

	// load mesh into a vertex buffer array
	meshes["carrot"] = Mesh("../Models/Trees/Carrot.obj", VAOS[0], phongProgramID);
	meshes["carrot"].generateObjectBufferMesh();
	meshes["carrot"].translateModel(vec3(-5.0, 0.0, 0.0));

	meshes["crystal"] = Mesh("../Models/Trees/Crystal.obj", VAOS[1], phongProgramID);
	meshes["crystal"].generateObjectBufferMesh();
	meshes["crystal"].translateModel(vec3(5.0, 0.0, 0.0));

	meshes["floor"] = Mesh("../Models/floor.obj", VAOS[2], phongProgramID);
	meshes["floor"].generateObjectBufferMesh();

	meshes["gino"] = Mesh("../Models/Chef Gino/Gino/Gino.dae", VAOS[3], phongProgramID);
	meshes["gino"].generateObjectBufferMesh();
	meshes["gino"].scaleModel(vec3(0.8, 0.8, 0.8));

	meshes["car"] = Mesh("../Models/Car/car.obj", VAOS[4], phongProgramID);
	meshes["car"].generateObjectBufferMesh();
	meshes["car"].translateModel(vec3(-10.0f, 0.6f, 10.0f));
	meshes["car"].scaleModel(vec3(2.0f, 2.0f, 2.0f));

	meshes["wheel1"] = Mesh("../Models/Car/wheel.obj", VAOS[5], phongProgramID);
	meshes["wheel1"].generateObjectBufferMesh();
	meshes["wheel1"].scaleModel(vec3(2.0f, 2.0f, 2.0f));

	meshes["wheel2"] = Mesh("../Models/Car/wheel.obj", VAOS[6], phongProgramID);
	meshes["wheel2"].generateObjectBufferMesh();
	meshes["wheel2"].scaleModel(vec3(2.0f, 2.0f, 2.0f));
	meshes["wheel2"].setRotation(3);

	meshes["wheel3"] = Mesh("../Models/Car/wheel.obj", VAOS[7], phongProgramID);
	meshes["wheel3"].generateObjectBufferMesh();
	meshes["wheel3"].scaleModel(vec3(2.0f, 2.0f, 2.0f));
	
	meshes["wheel4"] = Mesh("../Models/Car/wheel.obj", VAOS[8], phongProgramID);
	meshes["wheel4"].generateObjectBufferMesh();
	meshes["wheel4"].scaleModel(vec3(2.0f, 2.0f, 2.0f));
	meshes["wheel4"].setRotation(3);

}

// Placeholder code for the keypress
void keypress(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT) {
		meshes["gino"].translateModel(vec3(0.2f, 0.0f, 0.0f));
		meshes["gino"].setRotation(0);
	}
	if (key == GLUT_KEY_RIGHT) {
		meshes["gino"].translateModel(vec3(-0.2f, 0.0f, 0.0f));
		meshes["gino"].setRotation(1);
	}
	if (key == GLUT_KEY_UP) {
		meshes["gino"].translateModel(vec3(0.0f, 0.0f, 0.1f));
		meshes["gino"].setRotation(2);
	}
	if (key == GLUT_KEY_DOWN) {
		meshes["gino"].translateModel(vec3(0.0f, 0.0f, -0.1f));
		meshes["gino"].setRotation(3);
	}
	glutPostRedisplay();
}

void processNormalKeys(unsigned char key, int x, int y) {
	if (key == 'z') {
		if (zoom > 9.0f)
			zoom -= 1.0f;
	}
	if (key == 'x') {
		if (zoom < 24.0f)
			zoom += 1.0f;
	}
	if (key == 'q') {
		if (camera_alpha >= 355.0f) {
			camera_alpha = 5.0f;
		}
		else {
			camera_alpha += 5.0f;
		}
		
	}
	if (key == 'e') {
		if (camera_alpha <= 0.0f) {
			camera_alpha = 355.0f;
		}
		else {
			camera_alpha -= 5.0f;
		}
	}
}

unsigned int loadCubemap(std::vector<std::string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrComponents;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrComponents, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}