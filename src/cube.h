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

private:
	float* _vertices;
	unsigned int* _indices;
	VzShader* _shader;
	GLuint _vbo;
	GLuint _ebo;
	GLuint _vao;
	GLuint _texture;
};
