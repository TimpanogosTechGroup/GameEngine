/*
Isaac Draper

This is the implementation to manage loading assets to opengl.

NOT COMPLETE
*/
#include <vector>

#include "AssetManager.h"
#include "ResourceManager.h"
#include "Logger.h"

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
		*Logger::GetLogStream<AssetManager>() << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ :: " << vertexPath;
		Logger::LogClassStream<AssetManager>(LoggerLevel::ERROR);
		
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

	if (ResourceManager::hasTexture(file)) {
		Logger::Log<AssetManager>(DEBUG, "Already Loaded");
		return ResourceManager::getTexture(file);
	}
		

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
	}
	else
	{
		*Logger::GetLogStream<AssetManager>() << "Failed to load texture: " << file;
		Logger::LogClassStream<AssetManager>(LoggerLevel::ERROR);
	}
	stbi_image_free(data);

	ResourceManager::addTexture(file, texture);

	return texture;
}

Model* AssetManager::LoadModel(const char* pFile) {
	// not finished
	Model* model = new Model();

	// Create an instance of the Importer class
	Assimp::Importer importer;

	//check if file exists
	std::ifstream fin(pFile);
	if (!fin.fail()) {
		fin.close();
	}
	else {
		*Logger::GetLogStream<AssetManager>() << "Couldn't open this file : " << pFile;
		Logger::LogClassStream<AssetManager>(LoggerLevel::SEVERE);
		*Logger::GetLogStream<AssetManager>() << importer.GetErrorString();
		Logger::LogClassStream<AssetManager>(LoggerLevel::SEVERE);
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
		*Logger::GetLogStream<AssetManager>() << importer.GetErrorString();
		return nullptr;
	}
	else {
		*Logger::GetLogStream<AssetManager>() << pFile << ": Loaded";
		Logger::LogClassStream<AssetManager>(LoggerLevel::INFO);
	}

	std::vector<float> vertices;
	std::vector<float> colors;
	std::vector<float> normals;
	std::vector<float> uvs;

	bool hasTex = false;

	//*Logger::GetLogStream<AssetManager>() << "File: " << pFile << " INFO" << std::endl << "#Meshes: " << scene->mNumMeshes << std::endl;

	for (unsigned int n = 0; n < scene->mNumMeshes; n++) {
		const aiMesh* mesh = scene->mMeshes[n];
		int iMeshFaces = mesh->mNumFaces;

		for (int k = 0; k < iMeshFaces; k++) {
			const aiFace& face = mesh->mFaces[k];

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
					//*Logger::GetLogStream<AssetManager>() << mesh->mTextureCoords[0][face.mIndices[j]].x << mesh->mTextureCoords[0][face.mIndices[j]].y << std::endl;
				}
				else {
					uvs.push_back(1);
					uvs.push_back(1);
				}

				if (mesh->HasVertexColors(0)) {
					colors.push_back(mesh->mColors[face.mIndices[j]]->r);
					colors.push_back(mesh->mColors[face.mIndices[j]]->g);
					colors.push_back(mesh->mColors[face.mIndices[j]]->b);
				}
			}
		}

		Object* object = new Object(vertices, normals, uvs);
		object->SetMaterial(LoadMaterial(scene, mesh));
		model->AddObject(object);

		vertices.clear();
		colors.clear();
		normals.clear();
		uvs.clear();
	}

	// Everything (assimp) will be cleaned up by the importer destructor
	return model;
}

Material* AssetManager::LoadMaterial(const aiScene* scene, const aiMesh* mesh) {
	aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];
	aiString name;
	aiColor4D diffuse;

	aiTextureType textureType = aiTextureType_DIFFUSE;
	aiString texturePath;

	bool containsText = true;

	if (AI_SUCCESS != mat->Get(AI_MATKEY_NAME, name)) {
		*Logger::GetLogStream<AssetManager>() << "ERROR::LOAD_MODEL::LOAD_MATERIAL::Cannot load material";
		Logger::LogClassStream<AssetManager>(LoggerLevel::DEBUG);
	}
	else {
		aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &diffuse);
		//*Logger::GetLogStream<AssetManager>() << "Diffuse Color: " << diffuse.r << ", " << diffuse.g << ", " << diffuse.b << ", " << diffuse.a << " ";
	}
	if (mat->Get(AI_MATKEY_TEXTURE(textureType, 0), texturePath) == AI_SUCCESS) {
		*Logger::GetLogStream<AssetManager>() << "Loaded LOAD_MATERIAL: " << texturePath.C_Str();
		Logger::LogClassStream<AssetManager>(LoggerLevel::DEBUG);
		containsText = false;
	}
	//Shader* other = LoadShader("Shader\\color_vert.glsl", "Shader\\color_frag.glsl");
	Texture* texture = LoadTexture(texturePath.C_Str());
	Material* tmp = new Material(1, 1, texture, containsText ? ResourceManager::getShader("color_shader") : ResourceManager::getShader("texture_shader"), glm::vec4(diffuse.r, diffuse.g, diffuse.b, diffuse.a));
	return tmp;
}