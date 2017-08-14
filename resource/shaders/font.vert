#version 330 core
layout (location = 0) in vec4 PosTex; // <vec2 pos, vec2 tex>
out vec2 TexCoords;

uniform mat4 Projection;

void main()
{
	gl_position = Projection * vec4(PosTex.xy, 0.0, 1.0);
	TexCoords = PosTex.zw;
}