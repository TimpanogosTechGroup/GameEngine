#version 330 core 
layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 uvCoord;

out vec4 vertexColor;
out vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	gl_Position = projection * view * model * vec4(vertexPos, 1.0);
	vertexColor = vec4(color, 1.0);
	texCoord = uvCoord;
}