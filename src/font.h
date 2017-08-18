//---------------------------------------------------------
// Copyright (C) NSXTSoft. All rights reserved.

// ********************************************************
// File name : Font.h
// Created   : 2017/08/14 by SungHoon Ko
// ********************************************************
//
///////////////////////////////////////////////////////////
#pragma once

class VzFont {
public:
	VzFont();
	~VzFont();

public:
	void initialize() noexcept;
	void render_text(const std::string& text, const glm::vec2& pos, const glm::vec4& color, GLfloat scale) noexcept;
	void deinitialize() noexcept;

private:
	void _init_shader_obj();
	void _init_vertex_obj();	
	void _precache_ascii_charmap();

private:
	struct _CharacterInfo {
		GLuint texture_id;
		glm::ivec2 size;
		glm::ivec2 bearing;
		long advance;
	};

	std::map<GLchar, _CharacterInfo> _char_map;

private:
	VzShader* _shader;
	GLuint _vbo;
	GLuint _vao;

	glm::vec2 _position;
	glm::vec3 _color;
	float _scale;
	int _size;

	glm::mat4 _projection_matrix;
};
