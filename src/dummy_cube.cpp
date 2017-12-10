#include "core.h"
#include <stb/stb_image.h>
#include <glm/gtc/matrix_transform.hpp>

const float VzDummyCube::Vertices[] = {
	// positions			// texture coords
	-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,
	0.5f, -0.5f, -0.5f,		1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,		1.0f, 1.0f,
	0.5f,  0.5f, -0.5f,		1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
	0.5f, -0.5f,  0.5f,		1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,		1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,		1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,	0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,	1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,	1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,	1.0f, 0.0f,

	0.5f,  0.5f,  0.5f,		1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,		1.0f, 1.0f,
	0.5f, -0.5f, -0.5f,		0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,		0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,		0.0f, 0.0f,
	0.5f,  0.5f,  0.5f,		1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,		1.0f, 1.0f,
	0.5f, -0.5f,  0.5f,		1.0f, 0.0f,
	0.5f, -0.5f,  0.5f,		1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,
	0.5f,  0.5f, -0.5f,		1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,		1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,		1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,	0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,	0.0f, 1.0f
};

VzDummyCube::VzDummyCube(glm::vec3 pos) :	Position(pos), _shader(nullptr) {
}

VzDummyCube::~VzDummyCube() {
}

void VzDummyCube::destroy() {
	glDeleteVertexArrays(1, &_vao);
	glDeleteBuffers(1, &_vbo);	
	glDeleteTextures(1, &_texture1);
	glDeleteTextures(1, &_texture2);

	delete _shader;
}

void VzDummyCube::create() {
	_init_shader_obj();
	_init_vertex_obj();
	_init_texture_obj();

	ProjectionMatrix = VzCore::Camera.get_projection_matrix();
	ModelMatrix = glm::translate(ModelMatrix, Position);
}

void VzDummyCube::think() {
	ProjectionMatrix = VzCore::Camera.get_projection_matrix();
	ViewMatrix = VzCore::Camera.get_view_matrix();
}

void VzDummyCube::render() {

	think();
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _texture1);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, _texture2);

	_shader->use();
	_shader->set_mat4("projection", ProjectionMatrix);
	_shader->set_mat4("view", ViewMatrix);
	_shader->set_mat4("model", ModelMatrix);

	glBindVertexArray(_vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void VzDummyCube::_init_shader_obj() {
	auto vs_file_path = VzFileSystem::get_path("/resource/shaders/cube.vert");
	auto fs_file_path = VzFileSystem::get_path("/resource/shaders/cube.frag");
	if (vs_file_path.empty() || fs_file_path.empty()) {
		// TODO : Needs to process error message.
		std::cout << "ERROR:SHADER FILE LOAD FAIL." << std::endl;
		return;
	}
	_shader = new VzShader(vs_file_path.c_str(), fs_file_path.c_str());
}

void VzDummyCube::_init_vertex_obj() {
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);	

	glBindVertexArray(_vao);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void VzDummyCube::_init_texture_obj() {
	//----------------------------------------------
	// texture 1
	//
	glGenTextures(1, &_texture1);
	glBindTexture(GL_TEXTURE_2D, _texture1);

	// set the texture wrapping parameters
	// note that GL_REPEAT wrapping is default mode.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// set the texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load image, create texture and generate mipmaps
	auto tex1_file_path = VzFileSystem::get_path("/resource/textures/container.jpg");
	if (tex1_file_path.empty()) {
		// TODO : Needs to process error message.
		std::cout << "ERROR:TEXTURE FILE LOAD FAIL. : " << "/resource/textures/container.jpg" << std::endl;
		return;
	}

	// tell stb_image.h to flip loaded texture's on the y-axis.
	stbi_set_flip_vertically_on_load(true);

	int width, height, color_channels;
	unsigned char* data = stbi_load(tex1_file_path.c_str(), &width, &height, &color_channels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		// TODO : Needs to process error message.
		std::cout << "ERROR:TEXTURE FILE GENERATE FAIL. : " << "/resource/textures/container.jpg" << std::endl;
	}
	stbi_image_free(data);

	//----------------------------------------------
	// texture 2
	//
	glGenTextures(1, &_texture2);
	glBindTexture(GL_TEXTURE_2D, _texture2);

	// set the texture wrapping parameters
	// note that GL_REPEAT wrapping is default mode.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// set the texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load image, create texture and generate mipmaps
	auto tex2_file_path = VzFileSystem::get_path("/resource/textures/awesomeface.png");
	if (tex2_file_path.empty()) {
		// TODO : Needs to process error message.
		std::cout << "ERROR:TEXTURE FILE LOAD FAIL. : " << "/resource/textures/awesomeface.png" << std::endl;
		return;
	}

	data = stbi_load(tex2_file_path.c_str(), &width, &height, &color_channels, 0);
	if (data) {
		// note that the awesomeface.png had transparency and thus an alpha channel, 
		// so make sure to tell OpenGL the data type is of GL_RGBA
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		// TODO : Needs to process error message.
		std::cout << "ERROR:TEXTURE FILE GENERATE FAIL. : " << "/resource/textures/awesomeface.png" << std::endl;
	}
	stbi_image_free(data);

	//----------------------------------------------
	// bind to texture sampler2D in shader.
	//

	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	// don't forget to activate/use the shader before setting uniforms.
	_shader->use();
	_shader->set_int("texture1", 0);
	_shader->set_int("texture2", 1);
}

