//---------------------------------------------------------
// Copyright (C) NSXTSoft. All rights reserved.

// ********************************************************
// File name : square_matrix_entity.cpp
// Created   : 2017/09/20 by SungHoon Ko
// ********************************************************
//
///////////////////////////////////////////////////////////
#include "core.h"

float sm_vertices[] = {
	0.0f, 0.0f, 0.0f,	// V0 - bottom:front left
	1.0f, 0.0f, 0.0f,	// V1 - bottom:front right
	0.0f, 1.0f, 0.0f,	// V2 - top:front left
	1.0f, 1.0f, 0.0f,	// V3 - top:front right
};

unsigned int sm_indices[] = {
	0, 1,
	2, 3,
	0, 2,
	1, 3,
};

VzSquareMatrixEntity::VzSquareMatrixEntity() 
	: Position(glm::vec3(0.0f))
	, Orientation(glm::vec3(0.0f)) {
}

VzSquareMatrixEntity::~VzSquareMatrixEntity() {
}

void VzSquareMatrixEntity::create() {
	_init_shader();
	_init_geometry();
	_init_material();

	ProjectionMat = VzCore::Camera.get_projection_matrix();
	ModelMat = glm::translate(ModelMat, Position);
}

void VzSquareMatrixEntity::render() {
	
	think();

	_shader->use();
	_shader->set_mat4("projection", ProjectionMat);
	_shader->set_mat4("view", ViewMat);
	_shader->set_mat4("model", ModelMat);

	GLint last_blend_src_alpha; glGetIntegerv(GL_BLEND_SRC_ALPHA, &last_blend_src_alpha);
	GLboolean last_enable_blend = glIsEnabled(GL_BLEND);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBindVertexArray(_vao);
	glDrawElements(GL_LINES, sizeof(sm_indices), GL_UNSIGNED_INT, 0);

	glBlendFunc(GL_SRC_ALPHA, last_blend_src_alpha);
	if (last_enable_blend) glEnable(GL_BLEND); else glDisable(GL_BLEND);
}

void VzSquareMatrixEntity::destroy() {
	glDeleteVertexArrays(1, &_vao);
	glDeleteBuffers(1, &_vbo);
	glDeleteBuffers(1, &_ebo);
}

void VzSquareMatrixEntity::think() {
	ProjectionMat = VzCore::Camera.get_projection_matrix();
	ViewMat = VzCore::Camera.get_view_matrix();
}

void VzSquareMatrixEntity::_init_shader() {
	auto vsFilePath = VzFileSystem::get_path("/resource/shaders/square_matrix.vert");
	auto fsFilePath = VzFileSystem::get_path("/resource/shaders/square_matrix.frag");
	bool isValid = !(vsFilePath.empty() || fsFilePath.empty());

	BOOST_ASSERT_MSG(isValid, "ERROR: SHADER FILE LOAD FAIL.");
	if (!isValid)
		return;

	_shader = std::make_unique<VzShader>(vsFilePath.c_str(), fsFilePath.c_str());
}

void VzSquareMatrixEntity::_init_geometry() {

	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	glGenBuffers(1, &_ebo);

	glBindVertexArray(_vao);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sm_vertices), sm_vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(sm_indices), sm_indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void VzSquareMatrixEntity::_init_material() {
}
