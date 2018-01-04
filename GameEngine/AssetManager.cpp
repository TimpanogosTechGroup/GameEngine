/*
Isaac Draper

This is the implementation to manage loading assets to opengl.

NOT COMPLETE
*/
#include <vector>

#include "AssetManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include <glm\stb_image.h>

// ID is the id of the program the shader will be linked to - initial value will be changed
Shader* AssetManager::LoadShader(const char* vertexPath, const char* fragmentPath) {
	// 1. retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	std::ofstream output;

	output.open("test.txt");
	output << "Hello";
	output.close();


	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char * fShaderCode = fragmentCode.c_str();

	// 2. compile shaders
	Shader* shader = new Shader();

	Registry::GetRenderEngine()->CompileShader(SHADER_VERTEX, shader->vertex.GetID(), vShaderCode);
	Registry::GetRenderEngine()->CompileShader(SHADER_FRAGMENT, shader->fragment.GetID(), fShaderCode);
	Registry::GetRenderEngine()->LinkShaderProgram(*shader);
	
	return shader;
}

// basic version, eventually edit wrapping and filtering parameters
Texture* AssetManager::LoadTexture(const char* file) {
	Texture* texture = new Texture(); // Create a new texture
	// Genereate buffers and bind
	glGenTextures(1, &texture->GetID());
	glBindTexture(GL_TEXTURE_2D, texture->GetID());
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;

	unsigned char *data = stbi_load(file, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		texture->SetWidth(width);
		texture->SetHeight(height);

		//std::cout << "Loaded texture: " << data << std::endl;
		std::cout << "Texture: " << texture->GetID() << std::endl;
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl; // replace this to a call from the logger
	}
	stbi_image_free(data);

	return texture;
}

Object* AssetManager::LoadModel(const char* pFile, Texture* texture, Shader* shader) {
	// not finished

	// Create an instance of the Importer class
	Assimp::Importer importer;

	//check if file exists
	std::ifstream fin(pFile);
	if (!fin.fail()) {
		fin.close();
	}
	else {
		printf("Couldn't open file: %s\n", pFile);
		printf("%s\n", importer.GetErrorString());
	}

	// And have it read the given file with some example postprocessing
	// Usually - if speed is not the most important aspect for you - you'll 
	// propably request more postprocessing than we do in this example.
	const aiScene* scene = importer.ReadFile(pFile,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);

	// If the import failed, report it
	if (!scene) {
		std::cout << importer.GetErrorString() << std::endl;
	}
	else {
		std::cout << "Model loaded" << std::endl;
	}

	std::vector<float> vertices;
	std::vector<float> normals;
	std::vector<float> uvs;

	bool hasTex = false;

	for (unsigned int n = 0; n < scene->mNumMeshes; n++) {
		const aiMesh* mesh = scene->mMeshes[n];
		int iMeshFaces = mesh->mNumFaces;

		for (int k = 0; k < iMeshFaces; k++) {
			const aiFace& face = mesh->mFaces[k];
			//aiVector3D pos = mesh->mVertices[face.mIndices[k]];
			//aiVector3D uv = mesh->mTextureCoords[0][face.mIndices[k]];
			//aiVector3D normal = mesh->HasNormals() ? mesh->mNormals[face.mIndices[k]] : aiVector3D(1.0f, 1.0f, 1.0f);

			for (int j = 0; j < 3; j++) {
				vertices.push_back(mesh->mVertices[face.mIndices[j]].x);
				vertices.push_back(mesh->mVertices[face.mIndices[j]].y);
				vertices.push_back(mesh->mVertices[face.mIndices[j]].z);

				if (mesh->HasNormals()) {
					normals.push_back(mesh->mNormals[face.mIndices[j]].x);
					normals.push_back(mesh->mNormals[face.mIndices[j]].y);
					normals.push_back(mesh->mNormals[face.mIndices[j]].z);
				}
				else {
					normals.push_back(1);
					normals.push_back(1);
					normals.push_back(1);
				}

				if (mesh->HasTextureCoords(0)) {
					uvs.push_back(mesh->mTextureCoords[0][face.mIndices[j]].x);
					uvs.push_back(mesh->mTextureCoords[0][face.mIndices[j]].y);
				}
				else {
					uvs.push_back(1);
					uvs.push_back(1);
				}
			}

			//vertices.push_back(uv.x);
			//vertices.push_back(uv.y);
		}

		//for (int j = 0; j < mesh->mNumVertices; j++) {
		//	vertices.push_back(mesh->mVertices[j].x); vertices.push_back(mesh->mVertices[j].y); vertices.push_back(mesh->mVertices[j].z);
		//	normals.push_back(mesh->mNormals[n].x); normals.push_back(mesh->mNormals[n].y); normals.push_back(mesh->mNormals[n].z);
		//	if (mesh->HasTextureCoords(n)) {
		//		hasTex = true;
		//		uvs.push_back(mesh->mTextureCoords[n]->x); normals.push_back(mesh->mTextureCoords[n]->y);
		//	}
		//}
	}

	float* vertexArray = &vertices[0];
	float* normalArray = &normals[0];
	if (hasTex) {
		float* uvArray = &uvs[0];
		Object* object = new Object(vertexArray, normalArray, uvArray, vertices.size(), uvs.size());
	}
	Object* object = new Object(vertices, normals);
	object->SetMaterial(Material(1, 1, texture, shader, glm::vec3(1, 1, 1)));
	// TODO: replace above line with LoadMaterial
	// TODO: get textures (uv's are maybe not correct, need to check mTextureCoords and test more)

	LoadMaterial(scene);

	// Everything will be cleaned up by the importer destructor
	return object;
}

Material AssetManager::LoadMaterial(const aiScene* scene) {
	aiMaterial* mat = scene->mMaterials[0];
	aiString name;
	aiColor3D diffuse;
	aiColor3D specular;

	if (AI_SUCCESS != mat->Get(AI_MATKEY_NAME, name)) {
		std::cout << "ERROR::LOAD_MODEL::LOAD_MATERIAL::Cannot load material" << std::endl;
	}
	else {
		mat->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
		mat->Get(AI_MATKEY_COLOR_SPECULAR, specular);

		//TODO: finish loading material - convert aiColor3D (either to float (current) or vec3 (more likely))
	}

	Material tmp;
	return tmp;
}