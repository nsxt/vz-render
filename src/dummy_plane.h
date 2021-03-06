#pragma once

class VzDummyPlane {
public:
	const static float Vertices[];
	const static unsigned int Indices[];

public:
	glm::vec3 Position;
	glm::vec3 Orientaion;

public:
	VzDummyPlane() = default;
	VzDummyPlane(glm::vec3 pos);
	virtual ~VzDummyPlane() = default;

	void create();
	void render();
	void destroy();

private:
	void _init_shader_obj();
	void _init_vertex_obj();
	void _init_texture_obj();

private:
	VzShader* _shader;
	GLuint _vbo;
	GLuint _ebo;
	GLuint _vao;
	GLuint _texture1;
	GLuint _texture2;
};
