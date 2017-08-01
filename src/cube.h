#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

class VzShader;

class VzCube {
public:
	glm::vec3 Position;
	glm::vec3 Orientaion;

public:
	VzCube(glm::vec3 pos);
	~VzCube();

	void create();
	void render();
	void destroy();

private:
	void _init_shader_obj();
	void _init_vertex_obj();
	void _init_texture_obj();

private:
	float* _vertices;
	unsigned int* _indices;
	VzShader* _shader;
	GLuint _vbo;
	GLuint _ebo;
	GLuint _vao;
	GLuint _texture1;
	GLuint _texture2;
};
