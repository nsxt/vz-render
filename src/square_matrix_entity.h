//---------------------------------------------------------
// Copyright (C) NSXTSoft. All rights reserved.

// ********************************************************
// File name : square_matrix_entity.h
// Created   : 2017/09/20 by SungHoon Ko
// ********************************************************
//
///////////////////////////////////////////////////////////
#pragma once

class VzSquareMatrixEntity {
public:
	glm::vec3 Position;
	glm::vec3 Orientation;
	glm::mat4 ProjectionMat;
	glm::mat4 ViewMat;
	glm::mat4 ModelMat;

public:
	VzSquareMatrixEntity();
	~VzSquareMatrixEntity();

public:
	void create();
	void render();
	void destroy();

	void pre_think() {}
	void think();
	void post_think() {}

	void generate_matrix(unsigned extent = 17);

private:
	void _init_shader();
	void _init_geometry();
	void _init_material();

private:
	std::unique_ptr<VzShader> _shader;
	GLuint _vbo;
	GLuint _ebo;
	GLuint _vao;

	unsigned _square_extent;
	std::vector<glm::vec3> _vertices;
	std::vector<glm::uvec2> _indices;
};