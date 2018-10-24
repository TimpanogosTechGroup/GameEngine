#version 330 core 
layout (location = 0) in vec3 vertexPos;

out vec4 color;

void main() {
	gl_Position = vertexPos;
	vertexColor = vec4(1, 1, 1, 1);
}