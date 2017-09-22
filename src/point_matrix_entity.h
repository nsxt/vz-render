//---------------------------------------------------------
// Copyright (C) NSXTSoft. All rights reserved.

// ********************************************************
// File name : point_matrix_entity.h
// Created   : 2017/09/22 by SungHoon Ko
// ********************************************************
//
///////////////////////////////////////////////////////////
#pragma once

class VzPointMatrixEntity {
public:
	glm::vec3 Position;
	glm::vec3 Orientation;
	glm::mat4 ProjectionMat;
	glm::mat4 ViewMat;
	glm::mat4 ModelMat;

public:
	VzPointMatrixEntity();
	~VzPointMatrixEntity();

public:
	void create();
	void render();
	void destroy();

	void pre_think() {}
	void think();
	void post_think() {}

private:
	void _init_shader();
	void _init_geometry();
	void _init_material();

private:
	std::unique_ptr<VzShader> _shader;
	GLuint _vao;
	GLuint _vbo;

	std::vector<glm::vec3> _vertices;
};
