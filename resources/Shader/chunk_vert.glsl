#version 330 core
layout (location = 0) in vec3 vertexPos;
//layout (location = 1) in vec3 color;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 uvCoord;

out vec3 FragPos;
out vec3 Normal;
out vec3 vertexColor;
out vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = vec3(model * vec4(vertexPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;
	vertexColor = vec3(1, 1, 1);
	texCoord = uvCoord;

    gl_Position = projection * view * model * vec4(FragPos, 1.0);
}