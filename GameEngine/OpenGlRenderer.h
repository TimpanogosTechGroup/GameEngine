/**
	File: An OpenGL render implementation
    Purpose: This is an OpenGL implementation of the render engine. Will habndle all rendering in the game

    @author Ben Brenkman
    @version 1.0

	Copyright (c) 2018 All Rights Reserved
*/

#pragma once
#include <ft2build.h>
#include FT_FREETYPE_H
#include "RenderEngine.h"
#include <SDL\SDL.h>
#include "FrameBuffer.h"
#include "RegistryEntry.h"
#include "PhysicsEngine.h"
#include <string>
#include "CubeMap.h"
#include "Font.h"
#include "Chunk.h"

class OpenGlRenderer :
	public RenderEngine
{
public:
	OpenGlRenderer();
	~OpenGlRenderer();

	void CreateWindow(std::string name, int width, int height);
	void UpdateScreen();
	void BindFramBuffer(FrameBuffer* frame);
	void BindDefaultFrameBuffer();
	void Clear();

	// Graphics card calls
	bool CompileObject(Object& object);
	bool CompileModel(Model& model);
	bool CompileCubeMap(CubeMap& cubemap);
	void initFontBuffer(Font& font);
	//bool CompileObjectAtt(Object& object, char attributes); // Get this to work somehow, make a very flexible rendering function
	bool RenderObject(Camera& camera, Object& object, PhysicalInstance& pos);
	//bool RenderObject(Object& object, char attributes); // TODO send in the RenderItem and then specify how to render through the attributes char
	bool RenderModel(Camera& camera, Model& model);
	void RenderPhysicalInstance(Camera& camera, PhysicalInstance& model);
	void RenderCubeMap(Camera& camera, CubeMap& cube);
	void RenderText(Camera* camera, Font& font, std::string text, float x, float y, float scale, glm::vec3 color);
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
	// Renders the bounding box, these are different from normal Objects becuase we render them using GL_LINE_LOOP, and we have to change up the way OpenGlRenders stuff
	void RenderBoundingBox(Camera& camera, PhysicalInstance& physicalInstance, glm::vec3 color);
	// Initializes the renderer, this function loads default shaders and such
	void loadDefaults() override;
	// Renders the chunk, if the chunk has not been modified use the static index array
	void renderChunk(Camera* camera, Chunk* chunk);
	void compileChunk(Chunk* chunk);

	glm::mat4 getOrthoGraphicsProjection();

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