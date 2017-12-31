#include <iostream>
#include "OpenGlRenderer.h"
#include "AssetManager.h"
#include "Object.h"
#include "PrimitiveShape.h"
#include "Registry.h"
#include "FrameBuffer.h"

using namespace std;

int main(int argc, char** argv) {

	OpenGlRenderer renderer;
	renderer.CreateWindow(640, 480);
	renderer.UpdateScreen();
	renderer.SetStatus(RenderEngine::RUNNING);

	Registry::SetRenderEngine(&renderer);
	Registry::PrintClassName<OpenGlRenderer>();
	Shader* shader = AssetManager::LoadShader("Shader\\vert.glsl", "Shader\\frag.glsl");
	Texture* text = AssetManager::LoadTexture("Texture\\test.jpg");

	FrameBuffer* buffer = new FrameBuffer(640, 480, FrameBuffer::COLOR_BUFFER | FrameBuffer::STENCIL_DEPTH);
	FrameBuffer buffer2(640, 480, FrameBuffer::COLOR_BUFFER);
	buffer->Initialize();
	buffer2.Initialize();

	Object test = *PrimitiveShape::GenerateSquare(1, 1, Material(1, 1, text, shader, glm::vec3(1, 1, 0)));
	Object tes1 = *PrimitiveShape::GenerateSquare(-1, -1, Material(1, 1, text, shader, glm::vec3(0, 1, 1)));

	Object frame = *PrimitiveShape::GenerateSquare(1, 1, Material(1, 1, buffer->GetColorBuffer(), shader, glm::vec3(1, 1, 1)));
	Object frame2 = *PrimitiveShape::GenerateSquare(-1, -1, Material(1, 1, buffer2.GetColorBuffer(), shader, glm::vec3(1, 1, 1)));

	test.CreateBoundBox();
	tes1.CreateBoundBox();
	frame.CreateBoundBox();
	frame2.CreateBoundBox();

	std::cout << std::endl << "Bounding Boxes: " << std::endl;
	test.GetBoundBox().ToString();
	tes1.GetBoundBox().ToString();
	frame.GetBoundBox().ToString();
	frame2.GetBoundBox().ToString();

	std:cout << std::endl;
	
	renderer.CompileObject(test);
	renderer.CompileObject(tes1);
	renderer.CompileObject(frame);
	renderer.CompileObject(frame2);

	//std::cout << "Texture: " << buffer.GetColorBuffer()->GetID() << std::endl;

	// Main loop
	while (renderer.GetStatus() == RenderEngine::RUNNING) {

		renderer.BindFramBuffer(buffer);
		renderer.Clear();
		// We'll take out all of this input stuff out and make an InputManager class
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case  SDL_QUIT:
				renderer.SetStatus(RenderEngine::SHUTDOWN);
				break;
			}
		}
		
		renderer.RenderObject(test);
		renderer.RenderObject(tes1);

		renderer.BindFramBuffer(&buffer2);

		renderer.Clear();

		renderer.RenderObject(test);
		renderer.RenderObject(tes1);

		renderer.BindDefaultFrameBuffer();

		renderer.Clear();
		renderer.RenderObject(frame);
		renderer.RenderObject(frame2);

		renderer.UpdateScreen();
	}

	SDL_Quit();
	

	std::cout << "GameEngine" << std::endl;
	return 0;
}