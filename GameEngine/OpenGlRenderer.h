/*
Author: Ben Brenkman

Our OpenGl implementation of the RenderEngine
*/

#pragma once
#include "RenderEngine.h"
#include <SDL\SDL.h>
#include "FrameBuffer.h"
#include <string>

class OpenGlRenderer :
	public RenderEngine
{
public:
	OpenGlRenderer();
	~OpenGlRenderer();

	void CreateWindow(int width, int height);
	void UpdateScreen();
	void BindFramBuffer(FrameBuffer* frame);
	void BindDefaultFrameBuffer();
	void Clear();

	// Graphics card calls
	bool CompileObject(Object& object);
	bool CompileModel(Model& model);
	//bool CompileObjectAtt(Object& object, char attributes); // Get this to work somehow, make a very flexible rendering function
	bool RenderObject(Camera& camera, Object& object);
	//bool RenderObject(Object& object, char attributes); // TODO send in the RenderItem and then specify how to render through the attributes char
	bool RenderModel(Camera& camera, Model& model);

	// Compiles a shader and puts it onto the GPU, expects the ShaderType is it a fragment, vertex or geometry shader, and it needs the source code of that shader.
	// This function does not link the programs together, for that call LinkShaderProgram(Shader shader)
	bool CompileShader(ShaderType type, unsigned int &ID, const char* source) override;
	// Links all the shaders together
	bool LinkShaderProgram(Shader& shader) override;
	// Creates a framebuffer
	FrameBuffer* CreateFramebuffer(unsigned int width, unsigned int height) override;

	// Creates a bouding box buffer, they are a bit different from regular buffers, they dont have color verticies and we draw them using GL_LINE_LOOP
	void CompileBoundingBox(BoundingBox& boundingbox);
	// Renders the bounding box, these are different from normal Objects becuase we render them using GL_LINE_LOOP, and we have to change up the way OpenGlRenders stuff
	void RenderBoundingBox(Camera& camera, Model& model, glm::vec3 color);
	Shader bbShader;

	/*
	This section is for shaders, setting uniform values
	*/

	// Sets a unifmor vec2
	void SetUniformVec2(Shader* shader, const GLchar* name, glm::vec2 value);
	// Sets a unifmor vec3
	void SetUniformVec3(Shader* shader, const GLchar* name, glm::vec3 value);
	// Sets a unifmor float
	void SetUniformFloat(Shader* shader, const GLchar* name, float value);
	// Sets a unifmor int
	void SetUniformInt(Shader* shader, const GLchar* name, int value);
	// Sets a unifmor mat4
	void SetUniformMat4(Shader* shader, const GLchar* name, glm::mat4 value);


private:
	SDL_Window* window = NULL;
	SDL_GLContext context;

	bool CheckCompileErrors(GLuint shader, std::string type);
};