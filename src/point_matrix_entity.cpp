//---------------------------------------------------------
// Copyright (C) NSXTSoft. All rights reserved.

// ********************************************************
// File name : point_matrix_entity.cpp
// Created   : 2017/09/22 by SungHoon Ko
// ********************************************************
//
///////////////////////////////////////////////////////////
#include "core.h"

VzPointMatrixEntity::VzPointMatrixEntity() 
	: Position(glm::vec3(0.0f))
	, Orientation(glm::vec3(0.0f)) {
}

VzPointMatrixEntity::~VzPointMatrixEntity() {
}

void VzPointMatrixEntity::create() {

	_init_shader();
	_init_geometry();
	_init_material();

	ProjectionMat = VzCore::Camera.get_projection_matrix();
	ModelMat = glm::translate(ModelMat, Position);
}

void VzPointMatrixEntity::render() {
	if (_vertices.empty())
		return;
	
	think();

	_shader->use();
	_shader->set_mat4("projection", ProjectionMat);
	_shader->set_mat4("view", ViewMat);
	_shader->set_mat4("model", ModelMat);

	glBindVertexArray(_vao);

	auto verticesSize = _vertices.size() * sizeof(float) * 3;
	glDrawArrays(GL_POINTS, 0, verticesSize);
}

void VzPointMatrixEntity::destroy() {
	glDeleteVertexArrays(1, &_vao);
	glDeleteBuffers(1, &_vbo);
}

void VzPointMatrixEntity::think() {
	ProjectionMat = VzCore::Camera.get_projection_matrix();
	ViewMat = VzCore::Camera.get_view_matrix();
}

void VzPointMatrixEntity::_init_shader() {
	auto vsFilePath = VzFileSystem::get_path("/resource/shaders/point_matrix.vert");
	auto fsFilePath = VzFileSystem::get_path("/resource/shaders/point_matrix.frag");
	bool isValid = !(vsFilePath.empty() || fsFilePath.empty());

	BOOST_ASSERT_MSG(isValid, "ERROR: SHADER FILE LOAD FAIL.");
	if (!isValid)
		return;

	_shader = std::make_unique<VzShader>(vsFilePath.c_str(), fsFilePath.c_str());
}

void VzPointMatrixEntity::_init_geometry() {
}

void VzPointMatrixEntity::_init_material() {
}
