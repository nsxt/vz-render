#include "cube.h"
#include "shader.h"

float vertices[] = {
	// positions         // colors          // texture coords
	0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
	0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
	-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
	-0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
};
unsigned int indices[] = {
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
};

VzCube::VzCube(glm::vec3 pos) : 
	Position(pos), _vertices(nullptr), _indices(nullptr), _shader(nullptr) {
}

VzCube::~VzCube() {
}

void VzCube::create() {
	_vertices = vertices;
	_indices = indices;
}

void VzCube::render() {

}
