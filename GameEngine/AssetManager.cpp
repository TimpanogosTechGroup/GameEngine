/*
Isaac Draper

This is the implementation to manage loading assets to opengl.

NOT COMPLETE
*/

#include "AssetManager.h"
#include "Shader.h"
#include "Registry.h"

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
	Texture* texture = new Texture();
	unsigned int id;
	glGenTextures(1, &id);
	texture->SetId(id);
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

void AssetManager::LoadModel() {
	// working on assimp
}

void AssetManager::CheckCompileErrors(GLuint shader, std::string type)
{
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}