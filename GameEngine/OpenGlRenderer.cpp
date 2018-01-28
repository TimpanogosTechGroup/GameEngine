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
#include <glm\gtc\type_ptr.hpp>
#include "Camera.h"
#include <iterator>
#include <ostream>
#include <sstream>
#include "AssetManager.h"
#include "ResourceManager.h"
#include "Logger.h"
#include "Properties.h"

OpenGlRenderer::OpenGlRenderer()
{

}


OpenGlRenderer::~OpenGlRenderer()
{
}

// Creates a window
void OpenGlRenderer::CreateWindow(int width, int height) {

	window_width = width;
	window_height = height;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		Logger::Log<OpenGlRenderer>(SEVERE, "SDL could not initialize... :(");
	}
	else {

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

		//std::string version = static_cast<std::string>(glGetString(GL_VERSION));
		
		//*Logger::GetLogStream<OpenGlRenderer>() << "OpenGl Version: " << version;
		//Logger::LogClassStream<OpenGlRenderer>(LoggerLevel::INFO);

		// Creates a window
		window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
		if (window == NULL) {
			Logger::Log<OpenGlRenderer>(SEVERE, "Couldn't create window :(");
		}
		context = SDL_GL_CreateContext(window);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		// Setsup glew and sets the clear color (background color)
		glewInit();
		glClearColor(backgroundColor.r, backgroundColor.b, backgroundColor.g, 1);
		glViewport(0, 0, width, height);
		
		// Polygon mode is the way OpenGl renders the triangles, you can change the setting here to get wireframe mode
		if (Properties::Get<std::string>("renderMode") == "fill")
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		else if (Properties::Get<std::string>("renderMode") == "wireframe") {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		// Sets depth test so pixels rendererd underneath other pixels don't overrite those pixels (you get a really weird looking picture if you don't do this
		glEnable(GL_DEPTH_TEST);

		// Standard clear depth buffer bit and color buffer bit
		glClearDepth(1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		SDL_CaptureMouse(SDL_TRUE);
		//SDL_SetWindowGrab(window, SDL_TRUE);
		SDL_SetRelativeMouseMode(SDL_TRUE);
	}
}

void OpenGlRenderer::init() {
	ResourceManager::addShader("texture_shader", AssetManager::LoadShader("Shader\\light_vert.glsl", "Shader\\sun_frag.glsl"));
	ResourceManager::addShader("color_shader", AssetManager::LoadShader("Shader\\color_vert.glsl", "Shader\\color_frag.glsl"));
	ResourceManager::addShader("framebuffer", AssetManager::LoadShader("Shader\\transform_vert.glsl", "Shader\\transform_frag.glsl"));
}

// Swaps the render buffers so we can see the changes that we have rendered
void OpenGlRenderer::UpdateScreen() {
	// Updates the screen by swapping buffers
	SDL_GL_SwapWindow(window);
}

// Binds a framebuffer so we can render to it
void OpenGlRenderer::BindFramBuffer(FrameBuffer* frame) {
	glBindFramebuffer(GL_FRAMEBUFFER, frame->GetID());
	glViewport(0, 0, frame->GetColorBuffer()->GetWidth(), frame->GetColorBuffer()->GetHeight());
	glClearColor(frame->GetBackgroundColor().r, frame->GetBackgroundColor().b, frame->GetBackgroundColor().g, 1.0);
}

// Effectively unbinds the bound frame buffer setting it back to default render location.
void OpenGlRenderer::BindDefaultFrameBuffer() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, window_width, window_height);
	glClearColor(backgroundColor.r, backgroundColor.b, backgroundColor.g, 1.0);
}

// Graphics card calls
bool OpenGlRenderer::CompileObject(Object& object) {
	// First we need to create the buffer to send off to the GPU
	std::vector<float> buffer;

	//std::cout << "Compile start: Veticies: " << object.GetVerticies().Size() << std::endl;

	if (object.GetVerticies().Size() == object.GetNormals().Size()) {
		for (int i = 0; i < object.GetVerticies().Size(); i += 3) {
			buffer.push_back(object.GetVerticies().GetValues()[i]);
			buffer.push_back(object.GetVerticies().GetValues()[i + 1]);
			buffer.push_back(object.GetVerticies().GetValues()[i + 2]);

			buffer.push_back(object.GetMaterial()->GetColor().r);
			buffer.push_back(object.GetMaterial()->GetColor().g);
			buffer.push_back(object.GetMaterial()->GetColor().b);

			buffer.push_back(object.GetNormals().GetValues()[i]);
			buffer.push_back(object.GetNormals().GetValues()[i + 1]);
			buffer.push_back(object.GetNormals().GetValues()[i + 2]);

			//buffer.push_back(object.GetUVCoords().GetValues()[static_cast<int>(i * (2.0 / 3.0))]); // Need to cast it to int, because we need to use float for the calculation
			//buffer.push_back(object.GetUVCoords().GetValues()[static_cast<int>(i * (2.0 / 3.0)) + 1]);

			//std::cout << "UVCoord size: " << object.GetUVCoords().Size() << std::endl;
			//std::cout << "Verticie size: " << object.GetVerticies().Size() * (2.0 / 3.0) << std::endl;

			if (object.GetUVCoords().Size() < (object.GetVerticies().Size() * (2.0 / 3.0))) {
				buffer.push_back(0); // Need to cast it to int, because we need to use float for the calculation
				buffer.push_back(0);
			}
			else {
				int x = static_cast<int>(i * (2.0 / 3.0));
				buffer.push_back(object.GetUVCoords().GetValues()[x]);
				buffer.push_back(object.GetUVCoords().GetValues()[x + 1]);
				//std::cout << "Added texture coord: i, " << i << " x, " << x << " u, " << (object.GetUVCoords().GetValues()[x]) << " v, " << (object.GetUVCoords().GetValues()[x + 1]) <<  std::endl;
			}
		}

		//std::ostringstream oss;

		//if (!buffer.empty())
		//{
		//	// Convert all but the last element to avoid a trailing ","
		//	std::copy(buffer.begin(), buffer.end() - 1,
		//		std::ostream_iterator<float>(oss, ","));

		//	// Now add the last element with no delimiter
		//	oss << buffer.back();
		//}

		//std::cout << oss.str() << std::endl;
	}
	else {
		Logger::Log<OpenGlRenderer>(LoggerLevel::ERROR, "Not enough normals -> CompileObject()");
	}

	glGenVertexArrays(1, &object.GetID());
	glBindVertexArray(object.GetID());
	glGenBuffers(1, &object.VBO.GetID());

	glBindBuffer(GL_ARRAY_BUFFER, object.VBO.GetID());
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * buffer.size(), &buffer[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(9* sizeof(float)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return true;

}

bool OpenGlRenderer::CompileModel(Model& model) {
	OpenGlRenderer renderer;
	for (unsigned int i = 0; i < model.NumOfObjects(); i++) {
		renderer.CompileObject(*(model.GetObject(i)));
	}
	return true;
}

//bool CompileObjectAtt(Object& object, char attributes); // Get this to work somehow, make a very flexible rendering function
bool OpenGlRenderer::RenderObject(Camera& camera, Object& object) {

	// Generate the model matrix
	glm::mat4 model; // Create a indentity matrix
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // Apply a translation to the matrix
	//model = glm::rotate(model, 5.0f, glm::vec3(0.0, 0.0, 1.0)); // Rotate matrix
	//model = glm::scale(model, glm::vec3(0.5, 0.5, 0.5)); // Scale Matrix

	if (object.GetMaterial()->GetShader() != nullptr) {
		glUseProgram(object.GetMaterial()->GetShader()->GetID());
		//glUseProgram(3);
		//std::cout << "Using Shader: " << object.GetMaterial()->GetShader()->GetID() << std::endl;
		SetUniformMat4(object.GetMaterial()->GetShader(), "projection", camera.GetProjectionMatrix());
		SetUniformMat4(object.GetMaterial()->GetShader(), "view", camera.GetViewMatrix());
		glm::mat4 model;
		model = glm::translate(model, object.GetPostion());
		SetUniformMat4(object.GetMaterial()->GetShader(), "model", model);
	}

	//if (!(object.GetMaterial()->GetTexture()->GetID() < 0)) {
	//if (Properties::Get("renderMode") == "fill")
		glBindTexture(GL_TEXTURE_2D, object.GetMaterial()->GetTexture()->GetID());
	//else
		//glDisable(GL_TEXTURE_2D);
		//std::cout << object.GetMaterial()->GetTexture()->GetID();
	//}

	SetUniformVec3(object.GetMaterial()->GetShader(), "lightPos", glm::vec3(0, 10, 0));
	SetUniformVec3(object.GetMaterial()->GetShader(), "lightColor", glm::vec3(1, 0.9, 1));
	SetUniformVec3(object.GetMaterial()->GetShader(), "viewPos", camera.GetPosition());


	glBindVertexArray(object.GetID());
	glDrawArrays(GL_TRIANGLES, 0, object.GetVerticies().Size() / 3);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	return true;
}
//bool RenderObject(Object& object, char attributes);

bool OpenGlRenderer::RenderModel(Camera& camera, Model& model) {
	OpenGlRenderer renderer;
	for (unsigned int i = 0; i < model.NumOfObjects(); i++) {
		RenderObject(camera, *(model.GetObject(i)));
	}
	return true;
}

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
			*Logger::GetLogStream<OpenGlRenderer>() << "SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- ";
			Logger::LogClassStream<OpenGlRenderer>(LoggerLevel::ERROR);
		}
	}
	else
	{
		glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shaderID, 1024, NULL, infoLog);
			*Logger::GetLogStream<OpenGlRenderer>() << "PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- ";
			Logger::LogClassStream<OpenGlRenderer>(LoggerLevel::ERROR);
		}
	}
	return true;
}


// Create a new framebuffer and initializes it
FrameBuffer* OpenGlRenderer::CreateFramebuffer(unsigned int width, unsigned int height) {

	FrameBuffer* framebuffer = new FrameBuffer(width, height, 0);

	//unsigned int framebuffer;
	glGenFramebuffers(1, &framebuffer->GetID());
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer->GetID());

	// create a color attachment texture
	glGenTextures(1, &framebuffer->GetColorBuffer()->GetID());
	glBindTexture(GL_TEXTURE_2D, framebuffer->GetColorBuffer()->GetID());
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, framebuffer->GetColorBuffer()->GetWidth(), framebuffer->GetColorBuffer()->GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, framebuffer->GetColorBuffer()->GetID(), 0);
	// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)

	glGenRenderbuffers(1, &framebuffer->GetRbo()->GetID());
	glBindRenderbuffer(GL_RENDERBUFFER, framebuffer->GetRbo()->GetID());
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, framebuffer->GetWidth(), framebuffer->GetHeight()); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, framebuffer->GetRbo()->GetID()); // now actually attach it
																										  // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		Logger::Log<OpenGlRenderer>(LoggerLevel::ERROR, "ERROR::FRAMEBUFFER:: Framebuffer is not complete!");

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return framebuffer;
}

/*
This section is for shaders, setting uniform values
*/

// Sets a unifmor vec2
void OpenGlRenderer::SetUniformVec2(Shader* shader, const GLchar* name, glm::vec2 value) {
	int locaton = glGetUniformLocation(shader->GetID(), name);
	glUniform2f(locaton, value.x, value.y);
};
// Sets a unifmor vec3
void OpenGlRenderer::SetUniformVec3(Shader* shader, const GLchar* name, glm::vec3 value) {
	int locaton = glGetUniformLocation(shader->GetID(), name);
	glUniform3f(locaton, value.x, value.y, value.z);
};
// Sets a unifmor float
void OpenGlRenderer::SetUniformFloat(Shader* shader, const GLchar* name, float value) {
	int locaton = glGetUniformLocation(shader->GetID(), name);
	glUniform1f(locaton, value);
};
// Sets a unifmor int
void OpenGlRenderer::SetUniformInt(Shader* shader, const GLchar* name, int value) {
	int locaton = glGetUniformLocation(shader->GetID(), name);
	glUniform1i(locaton, value);
};
// Sets a unifmor mat4
void OpenGlRenderer::SetUniformMat4(Shader* shader, const GLchar* name, glm::mat4 value) {
	int locaton = glGetUniformLocation(shader->GetID(), name);
	glUniformMatrix4fv(locaton, 1, GL_FALSE, glm::value_ptr(value));
};

// Creates the bounding box mesh based on the info from the bounding box and loads it to the GPU, notice if you change the values in the bounding box you must recompile it!
void OpenGlRenderer::CompileBoundingBox(BoundingBox& boundingbox) {
	bbShader = *AssetManager::LoadShader("Shader\\bb_vert.glsl", "Shader\\bb_frag.glsl");
	// First we need to create the buffer to send off to the GPU
	std::vector<float> buffer;
	// First 8 verticies are rendered to produce to squares
	// 0
	buffer.push_back(boundingbox.GetxMin());
	buffer.push_back(boundingbox.GetyMin());
	buffer.push_back(boundingbox.GetzMin());
	// 1
	buffer.push_back(boundingbox.GetxMax());
	buffer.push_back(boundingbox.GetyMin());
	buffer.push_back(boundingbox.GetzMin());
	// 2
	buffer.push_back(boundingbox.GetxMax());
	buffer.push_back(boundingbox.GetyMax());
	buffer.push_back(boundingbox.GetzMin());
	// 3
	buffer.push_back(boundingbox.GetxMin());
	buffer.push_back(boundingbox.GetyMax());
	buffer.push_back(boundingbox.GetzMin());
	// 4
	buffer.push_back(boundingbox.GetxMin());
	buffer.push_back(boundingbox.GetyMin());
	buffer.push_back(boundingbox.GetzMax());
	// 5
	buffer.push_back(boundingbox.GetxMax());
	buffer.push_back(boundingbox.GetyMin());
	buffer.push_back(boundingbox.GetzMax());
	// 6
	buffer.push_back(boundingbox.GetxMax());
	buffer.push_back(boundingbox.GetyMax());
	buffer.push_back(boundingbox.GetzMax());
	// 7
	buffer.push_back(boundingbox.GetxMin());
	buffer.push_back(boundingbox.GetyMax());
	buffer.push_back(boundingbox.GetzMax());

	// Final 8 verticeis are used to connect the 2 squares to make the cube shape
	// 0
	buffer.push_back(boundingbox.GetxMin());
	buffer.push_back(boundingbox.GetyMin());
	buffer.push_back(boundingbox.GetzMin());
	// 4
	buffer.push_back(boundingbox.GetxMin());
	buffer.push_back(boundingbox.GetyMin());
	buffer.push_back(boundingbox.GetzMax());
	// 1
	buffer.push_back(boundingbox.GetxMax());
	buffer.push_back(boundingbox.GetyMin());
	buffer.push_back(boundingbox.GetzMin());
	// 5
	buffer.push_back(boundingbox.GetxMax());
	buffer.push_back(boundingbox.GetyMin());
	buffer.push_back(boundingbox.GetzMax());
	// 2
	buffer.push_back(boundingbox.GetxMax());
	buffer.push_back(boundingbox.GetyMax());
	buffer.push_back(boundingbox.GetzMin());
	// 6
	buffer.push_back(boundingbox.GetxMax());
	buffer.push_back(boundingbox.GetyMax());
	buffer.push_back(boundingbox.GetzMax());
	// 3
	buffer.push_back(boundingbox.GetxMin());
	buffer.push_back(boundingbox.GetyMax());
	buffer.push_back(boundingbox.GetzMin());
	// 7
	buffer.push_back(boundingbox.GetxMin());
	buffer.push_back(boundingbox.GetyMax());
	buffer.push_back(boundingbox.GetzMax());

	//std::ostringstream oss;

	//// Convert all but the last element to avoid a trailing ","
	//std::copy(buffer.begin(), buffer.end() - 1,
	//std::ostream_iterator<float>(oss, ","));

	//// Now add the last element with no delimiter
	//oss << buffer.back();
	//std::cout << oss.str() << std::endl;

	glGenVertexArrays(1, &boundingbox.GetID());
	glBindVertexArray(boundingbox.GetID());
	glGenBuffers(1, &boundingbox.VBO.GetID());

	glBindBuffer(GL_ARRAY_BUFFER, boundingbox.VBO.GetID());
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * buffer.size(), &buffer[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Renderes the bounding box with the view of the camera and color given in
void OpenGlRenderer::RenderBoundingBox(Camera& camera, Model& modelO, glm::vec3 color) {
	//glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1, 0);
	glLineWidth(Properties::Get<float>("glLineWidth"));

	glUseProgram(bbShader.GetID());
	SetUniformMat4(&bbShader, "projection", camera.GetProjectionMatrix());
	SetUniformMat4(&bbShader, "view", camera.GetViewMatrix());
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));
	SetUniformMat4(&bbShader, "model", model);
	SetUniformVec3(&bbShader, "color", color);

	glBindVertexArray(modelO.boundingBox.GetID());
	glDrawArrays(GL_LINE_LOOP, 0, 4);
	glDrawArrays(GL_LINE_LOOP, 4, 4);
	glDrawArrays(GL_LINES, 8, 8);
	glBindVertexArray(0);
}