#version 330 core

layout (location = 0) in vec3 inPos;

out vec4 VertexColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(inPos, 1.0f);
	VertexColor = vec4(0.9, 0.9, 0.9, 0.2);
}
