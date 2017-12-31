/*
Author: Ben Brenkman
Notes: This is the rendering class for OpenGl, all calls related to OpenGl should be located in here. But for now do what you can.
		This class will help create windows, change frambuffers, bind textures, render objects, and do all that crazy rending stuff
*/

#include "OpenGlRenderer.h"
#include <iostream>
#include <vector>
#include <string>
#include <GLEW\glew.h>
#include <glm\gtc\matrix_transform.hpp>

OpenGlRenderer::OpenGlRenderer()
{

}


OpenGlRenderer::~OpenGlRenderer()
{
}

// Creates a window
void OpenGlRenderer::CreateWindow(int width, int height) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "SDL could not initialize: " << std::endl;
	}
	else {
		// Creates a window
		window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
		if (window == NULL) {
			std::cout << "Couldn't create window :(";
		}
		context = SDL_GL_CreateContext(window);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		// Setsup glew and sets the clear color (background color)
		glewInit();
		glClearColor(0.3, 0.3, 0.3, 1);
		glViewport(0, 0, width, height);
		
		// Polygon mode is the way OpenGl renders the triangles, you can change the setting here to get wireframe mode
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		// Sets depth test so pixels rendererd underneath other pixels don't overrite those pixels (you get a really weird looking picture if you don't do this
		glEnable(GL_DEPTH_TEST);


		// Standard clear depth buffer bit and color buffer bit
		glClearDepth(1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}

// Swaps the render buffers so we can see the changes that we have rendered
void OpenGlRenderer::UpdateScreen() {
	// Updates the screen by swapping buffers
	SDL_GL_SwapWindow(window);
}

// Binds a framebuffer so we can render to it
void OpenGlRenderer::BindFramBuffer(FrameBuffer* frame) {
	glBindFramebuffer(GL_FRAMEBUFFER, frame->GetID());
}

// Effectively unbinds the bound frame buffer setting it back to default render location.
void OpenGlRenderer::BindDefaultFrameBuffer() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

// Graphics card calls
bool OpenGlRenderer::CompileObject(Object& object) {
	// First we need to create the buffer to send off to the GPU
	std::vector<float> buffer;

	for (int i = 0; i < object.GetVerticies().Size(); i += 3) {
		buffer.push_back(object.GetVerticies().GetValues()[i]);
		buffer.push_back(object.GetVerticies().GetValues()[i + 1]);
		buffer.push_back(object.GetVerticies().GetValues()[i + 2]);

		buffer.push_back(object.GetMaterial()->GetColor().r);
		buffer.push_back(object.GetMaterial()->GetColor().g);
		buffer.push_back(object.GetMaterial()->GetColor().b);

		buffer.push_back(object.GetUVCoords().GetValues()[static_cast<int>(i * (2.0 / 3.0))]); // Need to cast it to int, because we need to use float for the calculation
		buffer.push_back(object.GetUVCoords().GetValues()[static_cast<int>(i * (2.0 / 3.0)) + 1]);
	}

	glGenVertexArrays(1, &object.GetID());
	glBindVertexArray(object.GetID());
	glGenBuffers(1, &object.VBO.GetID());

	glBindBuffer(GL_ARRAY_BUFFER, object.VBO.GetID());
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * buffer.size(), &buffer[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return true;

}
//bool CompileObjectAtt(Object& object, char attributes); // Get this to work somehow, make a very flexible rendering function
bool OpenGlRenderer::RenderObject(Object& object) {

	// Generate the model matrix
	glm::mat4 model; // Create a indentity matrix
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // Apply a translation to the matrix
	//model = glm::rotate(model, 5.0f, glm::vec3(0.0, 0.0, 1.0)); // Rotate matrix
	//model = glm::scale(model, glm::vec3(0.5, 0.5, 0.5)); // Scale Matrix

	if (object.GetMaterial()->GetShader() != nullptr) {
		glUseProgram(object.GetMaterial()->GetShader()->GetID());
		//glUseProgram(3);
		//std::cout << "Using Shader: " << object.GetMaterial()->GetShader()->GetID() << std::endl;
	}

	if (object.GetMaterial()->GetTexture() != nullptr) {
		glBindTexture(GL_TEXTURE_2D, object.GetMaterial()->GetTexture()->GetID());
	}

	glBindVertexArray(object.GetID());
	glDrawArrays(GL_TRIANGLES, 0, object.GetVerticies().Size() / 3);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	return true;
}
//bool RenderObject(Object& object, char attributes);

void OpenGlRenderer::Clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// Compiles a shader and puts it onto the GPU, expects the ShaderType is it a fragment, vertex or geometry shader, and it needs the source code of that shader.
// This function does not link the programs together, for that call LinkShaderProgram(Shader shader)
bool OpenGlRenderer::CompileShader(ShaderType type, unsigned int &ID, const char* source) {
	switch (type) {
	case SHADER_VERTEX:
		// vertex shader
		ID = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(ID, 1, &source, NULL);
		glCompileShader(ID);
		return CheckCompileErrors(ID, "VERTEX");
		break;
	case SHADER_FRAGMENT:
		// fragment Shader
		ID = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(ID, 1, &source, NULL);
		glCompileShader(ID);
		return CheckCompileErrors(ID, "FRAGMENT");
		break;
	case SHADER_GEOMETRY:
		// geometry Shader
		ID = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(ID, 1, &source, NULL);
		glCompileShader(ID);
		return CheckCompileErrors(ID, "GEOMETRY");
		break;
	}
	return true;
}
// Links all the shaders together
bool OpenGlRenderer::LinkShaderProgram(Shader& shader) {
	// shader Program
	shader.GetID() = glCreateProgram();
	std::cout << "Created Shader: " << shader.GetID() << std::endl;
	glAttachShader(shader.GetID(), shader.vertex.GetID());
	glAttachShader(shader.GetID(), shader.fragment.GetID());
	glLinkProgram(shader.GetID());
	CheckCompileErrors(shader.GetID(), "PROGRAM");
	// delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(shader.vertex.GetID());
	glDeleteShader(shader.fragment.GetID());
	return true;
}

bool OpenGlRenderer::CheckCompileErrors(GLuint shaderID, std::string type)
{
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shaderID, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shaderID, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	return true;
}