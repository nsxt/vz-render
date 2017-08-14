//---------------------------------------------------------
// Copyright (C) NSXTSoft. All rights reserved.

// ********************************************************
// File name : VzFont.cpp
// Created   : 2017/08/14 by SungHoon Ko
// ********************************************************
//
///////////////////////////////////////////////////////////
#include "core.h"

VzFont::VzFont() 
	: _shader{ nullptr }, _vbo{ 0 }, _vao{ 0 }, _position{ glm::vec2(0.0f, 0.0f) }
	, _color{ glm::vec3(0.0f, 0.0f, 0.0f) }, _scale{ 1.0f }, _size{ 48 } {
}

VzFont::~VzFont() {
}

void VzFont::initialize() {
	_init_shader_obj();
	_init_vertex_obj();
}

void VzFont::precache_ascii_charmap() {

}

void VzFont::render_text() {

}

void VzFont::deinitialize() {
	glDeleteVertexArrays(1, &_vao);
	glDeleteBuffers(1, &_vbo);
	delete _shader;
}

void VzFont::_init_shader_obj() {
	auto vs_file_path = VzFileSystem::get_path("/resource/shaders/font.vert");
	auto fs_file_path = VzFileSystem::get_path("/resource/shaders/font.frag");
	if (vs_file_path.empty() || fs_file_path.empty()) {
		// TODO : Needs to process error message.
		std::cout << "ERROR:SHADER FILE LOAD FAIL." << std::endl;
		return;
	}
	_shader = new VzShader(vs_file_path.c_str(), fs_file_path.c_str());
}

void VzFont::_init_vertex_obj() {
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);

	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void VzFont::_init_texture_obj() {
}

