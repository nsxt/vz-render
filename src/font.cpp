//---------------------------------------------------------
// Copyright (C) NSXTSoft. All rights reserved.

// ********************************************************
// File name : VzFont.cpp
// Created   : 2017/08/14 by SungHoon Ko
// ********************************************************
//
///////////////////////////////////////////////////////////
#include "core.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

VzFont::VzFont() 
	: _shader{ nullptr }, _vbo{ 0 }, _vao{ 0 }, _position{ glm::vec2(0.0f, 0.0f) }
	, _color{ glm::vec3(0.0f, 0.0f, 0.0f) }, _scale{ 1.0f }, _size{ 48 } {
}

VzFont::~VzFont() {
}

void VzFont::initialize() {
	_init_shader_obj();
	_init_vertex_obj();

	int w, h;
	VzCore::Camera.get_screen_size(w, h);
	_projection_matrix = glm::ortho(0.0f, static_cast<float>(w), 0.0f, static_cast<float>(h));

	_shader->use();
	_shader->set_mat4("Projection", _projection_matrix);
}

void VzFont::precache_ascii_charmap() {	
	// All function return a value different than 0 thenever an error occurred
	FT_Library ft;
	if (FT_Init_FreeType(&ft))
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

	// Load font as face
	FT_Face face;
	std::string font_path = VzFileSystem::get_path("/resource/fonts/D2Coding.ttf");
	if (FT_New_Face(ft, font_path.c_str(), 0, &face))
		std::cout << "EROOR::FREETYPE: Failed to load font" << std::endl;

	// Set size to load glyphs as
	FT_Set_Pixel_Sizes(face, 0, 48);

	// Disable byte-alignment restriction
	GLint last_pixel_unpack_alignment;
	glGetIntegerv(GL_UNPACK_ALIGNMENT, &last_pixel_unpack_alignment);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Load first 128 characters of ASCII set
	for (GLubyte c = 0; c < 128; c++) {
		// Load character glyph
		if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
			std::cout << "ERROR::FREETYPE: Failed to load Glyph" << std::endl;
			continue;
		}

		// Generate texture
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexImage2D(
			GL_TEXTURE_2D, 0, GL_RED,
			face->glyph->bitmap.width, face->glyph->bitmap.rows,
			0, GL_RED, GL_UNSIGNED_BYTE, 
			face->glyph->bitmap.buffer
		);

		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		_CharacterInfo char_info = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};

		_char_map.insert(std::pair<GLchar, _CharacterInfo>(c, char_info));
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	glPixelStorei(GL_UNPACK_ALIGNMENT, last_pixel_unpack_alignment);

	// Destroy FreeType once we're finished
	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}

void VzFont::render_text() {
	GLint last_blend_src_alpha; glGetIntegerv(GL_BLEND_SRC_ALPHA, &last_blend_src_alpha);
	GLboolean last_enable_cull_face = glIsEnabled(GL_CULL_FACE);
	GLboolean last_enable_blend = glIsEnabled(GL_BLEND);
	GLboolean last_enable_depth_test = glIsEnabled(GL_DEPTH_TEST);
	GLboolean last_enable_scissor_test = glIsEnabled(GL_SCISSOR_TEST);





	glBlendFunc(GL_SRC_ALPHA, last_blend_src_alpha);
	if (last_enable_blend) glEnable(GL_BLEND); else glDisable(GL_BLEND);
	if (last_enable_cull_face) glEnable(GL_CULL_FACE); else glDisable(GL_CULL_FACE);
	if (last_enable_depth_test) glEnable(GL_DEPTH_TEST); else glDisable(GL_DEPTH_TEST);
	if (last_enable_scissor_test) glEnable(GL_SCISSOR_TEST); else glDisable(GL_SCISSOR_TEST);
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

