/*
Author: Ben Brenkman

Our OpenGl implementation of the RenderEngine
*/

#pragma once
#include "RenderEngine.h"
#include <SDL\SDL.h>
#include "FrameBuffer.h"

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
	//bool CompileObjectAtt(Object& object, char attributes); // Get this to work somehow, make a very flexible rendering function
	bool RenderObject(Object& object);
	bool RenderObject(Object& object, int id);
	//bool RenderObject(Object& object, char attributes); // TODO send in the RenderItem and then specify how to render through the attributes char

	// Compiles a shader and puts it onto the GPU, expects the ShaderType is it a fragment, vertex or geometry shader, and it needs the source code of that shader.
	// This function does not link the programs together, for that call LinkShaderProgram(Shader shader)
	bool CompileShader(ShaderType type, unsigned int &ID, const char* source) override;
	// Links all the shaders together
	bool LinkShaderProgram(Shader& shader) override;

private:
	SDL_Window* window = NULL;
	SDL_GLContext context;

	bool CheckCompileErrors(GLuint shader, std::string type);
};

