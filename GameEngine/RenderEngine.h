/*
Author: Ben Brenkman

This is the RenderEngine class, we will have different implementations of this class that will help us keep our code really clean and prevent breaking and a lot of heart ache when we expand and try and implement VR, DirectX or go mobile
*/
#pragma once
#include "Object.h"
#include "Model.h"
#include "FrameBuffer.h"
#include "Camera.h"
#include "RegistryEntry.h"

class RenderEngine : public RegistryEntry {
public:
	void CreateWindow(int width, int height);
	void UpdateScreen();
	enum Status { RUNNING, ERROR, SHUTDOWN };
	Status GetStatus() { return status; };
	void SetStatus(Status stat) { status = stat; };
	void Clear();

	void SetBackgroundColor(glm::vec3 color) { backgroundColor = color; };

	// Graphics card calls
	bool CompileObject(Object& object);
	bool CompileModel(Model& model);
	//bool CompileObjectAtt(Object& object, char attributes); // Get this to work somehow, make a very flexible rendering function
	bool RenderObject(Camera& camera, Object& object);
	//bool RenderObject(Object& object, char attributes);
	//bool RenderModel(Camera& camera, Model& model);

	// Compiles a shader and puts it onto the GPU, expects the ShaderType is it a fragment, vertex or geometry shader, and it needs the source code of that shader.
	// This function does not link the programs together, for that call LinkShaderProgram(Shader shader)
	virtual bool CompileShader(ShaderType type, unsigned int &ID, const char* source) { return true; };
	// Links all the shaders together
	virtual bool LinkShaderProgram(Shader& shader) { return true; };
	// Creates a framebuffer
	virtual FrameBuffer* CreateFramebuffer(unsigned int width, unsigned int height) { return nullptr; };
	// initializes the render engine AFTER calling create window
	virtual void init() {};

	// Gets the screen width and height
	int GetWidth() { return window_width; };
	int GetHeight() { return window_height; };


protected:
	int window_height = 0;
	int window_width = 0;
	Status status;
	glm::vec3 backgroundColor = glm::vec3(0, 0, 0);
};