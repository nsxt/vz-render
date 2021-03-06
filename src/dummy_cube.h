#pragma once

class VzDummyCube {
public:
	const static float Vertices[];	

public:
	glm::vec3 Position;
	glm::vec3 Orientaion;

	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;
	glm::mat4 ModelMatrix;

public:
	VzDummyCube() = default;
	VzDummyCube(glm::vec3 pos);
	virtual ~VzDummyCube();

	void create();
	void render();
	void destroy();

	void pre_think() {}
	void think();
	void post_think() {}

private:
	void _init_shader_obj();
	void _init_vertex_obj();
	void _init_texture_obj();

private:
	VzShader* _shader;
	GLuint _vbo;	
	GLuint _vao;
	GLuint _texture1;
	GLuint _texture2;
};

