#include "Mesh.hpp"

Mesh::Mesh(const char* fn, unsigned int vao, GLuint spID) {
	this->file_name = fn;
	this->shaderProgramID = spID;
	this->vao = vao;
	model = identity_mat4();
	modelRot = identity_mat4();
	modelScale = identity_mat4();
	modelTrans = identity_mat4();
	rot_z = 0.0f;
}

Mesh::Mesh() {
	this->file_name = "toilet.obj";
	this->shaderProgramID = 1;
	model = identity_mat4();
	modelRot = identity_mat4();
	modelScale = identity_mat4();
	modelTrans = identity_mat4();
	rot_z = 0.0f;
}


void Mesh::scaleModel(vec3 scaleMat) {
	modelScale = scale(modelScale, scaleMat);
}

void Mesh::translateModel(vec3 translateMat) {
	modelTrans = translate(modelTrans, translateMat);
}

void Mesh::rotate_z_axis(float degrees) {
	rot_z +=  degrees;
}

void Mesh::setTransMat(vec3 translateMat) {
	modelTrans = translate(identity_mat4(), translateMat);
}

void Mesh::setRotation(int i) {
	if (i < 4 && i >= 0)
		currentRot = i;
}

void Mesh::setInnerRotation() {
	switch (currentRot)
	{
	case 0: // Left
		modelRot = rotate_y_deg(modelRot, 90.0f);
		break;
	case 1: // Right
		modelRot = rotate_y_deg(modelRot, -90.0f);
		break;
	case 2: // Up
		modelRot = rotate_y_deg(modelRot, 0.0f);
		break;
	case 3: // Down
		modelRot = rotate_y_deg(modelRot, 180.0f);
		break;
	default:
		break;
	}
}

mat4 Mesh::getModel() {
	modelRot = identity_mat4();
	setInnerRotation();
	modelRot = rotate_z_deg(modelRot, rot_z);
	return modelTrans * (modelRot * (modelScale * model));
}

glm::vec3 Mesh::getModelCoord() {
	return glm::vec3(modelTrans.m[12], modelTrans.m[13], modelTrans.m[14]);
}

ModelData Mesh::load_mesh(const char* file_name) {
	ModelData modelData;

	/* Use assimp to read the model file, forcing it to be read as    */
	/* triangles. The second flag (aiProcess_PreTransformVertices) is */
	/* relevant if there are multiple meshes in the model file that   */
	/* are offset from the origin. This is pre-transform them so      */
	/* they're in the right position.                                 */
	const aiScene* scene = aiImportFile(
		file_name,
		aiProcess_Triangulate | aiProcess_PreTransformVertices
	);

	if (!scene) {
		fprintf(stderr, "ERROR: reading mesh %s\n", file_name);
		return modelData;
	}

	printf("  %i materials\n", scene->mNumMaterials);
	printf("  %i meshes\n", scene->mNumMeshes);
	printf("  %i textures\n", scene->mNumTextures);

	for (unsigned int m_i = 0; m_i < scene->mNumMeshes; m_i++) {
		const aiMesh* mesh = scene->mMeshes[m_i];
		printf("    %i vertices in mesh\n", mesh->mNumVertices);
		modelData.mPointCount += mesh->mNumVertices;
		for (unsigned int v_i = 0; v_i < mesh->mNumVertices; v_i++) {
			if (mesh->HasPositions()) {
				const aiVector3D* vp = &(mesh->mVertices[v_i]);
				modelData.mVertices.push_back(vec3(vp->x, vp->y, vp->z));
			}
			if (mesh->HasNormals()) {
				const aiVector3D* vn = &(mesh->mNormals[v_i]);
				modelData.mNormals.push_back(vec3(vn->x, vn->y, vn->z));
			}
			if (mesh->HasTextureCoords(0)) {
				const aiVector3D* vt = &(mesh->mTextureCoords[0][v_i]);
				modelData.mTextureCoords.push_back(vec2(vt->x, vt->y));
			}
			if (mesh->HasTangentsAndBitangents()) {
				/* You can extract tangents and bitangents here              */
				/* Note that you might need to make Assimp generate this     */
				/* data for you. Take a look at the flags that aiImportFile  */
				/* can take.                                                 */
			}
		}
	}

	aiReleaseImport(scene);
	return modelData;
}

// VBO Functions - click on + to expand
#pragma region VBO_FUNCTIONS
void Mesh::generateObjectBufferMesh() {
	/*----------------------------------------------------------------------------
	LOAD MESH HERE AND COPY INTO BUFFERS
	----------------------------------------------------------------------------*/

	//Note: you may get an error "vector subscript out of range" if you are using this code for a mesh that doesnt have positions and normals
	//Might be an idea to do a check for that before generating and binding the buffer.

	mesh_data = load_mesh(this->file_name);
	unsigned int vp_vbo = 0;
	loc1 = glGetAttribLocation(shaderProgramID, "vertex_position");
	loc2 = glGetAttribLocation(shaderProgramID, "vertex_normal");
	loc3 = glGetAttribLocation(shaderProgramID, "vertex_texture");

	glGenBuffers(1, &vp_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vp_vbo);
	glBufferData(GL_ARRAY_BUFFER, mesh_data.mPointCount * sizeof(vec3), &mesh_data.mVertices[0], GL_STATIC_DRAW);
	unsigned int vn_vbo = 0;
	glGenBuffers(1, &vn_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vn_vbo);
	glBufferData(GL_ARRAY_BUFFER, mesh_data.mPointCount * sizeof(vec3), &mesh_data.mNormals[0], GL_STATIC_DRAW);

	//	This is for texture coordinates which you don't currently need, so I have commented it out
	//	unsigned int vt_vbo = 0;
	//	glGenBuffers (1, &vt_vbo);
	//	glBindBuffer (GL_ARRAY_BUFFER, vt_vbo);
	//	glBufferData (GL_ARRAY_BUFFER, monkey_head_data.mTextureCoords * sizeof (vec2), &monkey_head_data.mTextureCoords[0], GL_STATIC_DRAW);
	
	glBindVertexArray(vao);

	glEnableVertexAttribArray(loc1);
	glBindBuffer(GL_ARRAY_BUFFER, vp_vbo);
	glVertexAttribPointer(loc1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(loc2);
	glBindBuffer(GL_ARRAY_BUFFER, vn_vbo);
	glVertexAttribPointer(loc2, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	//	This is for texture coordinates which you don't currently need, so I have commented it out
	//	glEnableVertexAttribArray (loc3);
	//	glBindBuffer (GL_ARRAY_BUFFER, vt_vbo);
	//	glVertexAttribPointer (loc3, 2, GL_FLOAT, GL_FALSE, 0, NULL);
}
#pragma endregion VBO_FUNCTIONS

