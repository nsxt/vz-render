#version 330 core

layout (location = 0) in vec3 Pos_in;
layout (location = 1) in vec3 Color_in;
layout (location = 2) in vec2 TexCoord_in;

out vec3 Color_vs;
out vec2 TexCoord_vs;

void main() 
{
	gl_Position = vec4(Pos_in, 1.0);
	Color_vs = Color_in;
	TexCoord_vs = vec2(TexCoord_in.x, TexCoord_in.y);
}