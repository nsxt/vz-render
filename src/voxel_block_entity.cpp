//---------------------------------------------------------
// Copyright (C) NSXTSoft. All rights reserved.

// ********************************************************
// File name : voxel_block_entity.cpp
// Created   : 2017/09/07 by SungHoon Ko
// ********************************************************
//
///////////////////////////////////////////////////////////
#include "core.h"

VzVoxelBlockEntity::VzVoxelBlockEntity() {
}

VzVoxelBlockEntity::~VzVoxelBlockEntity() {
}

void VzVoxelBlockEntity::create() {
	_init_shader();
	_init_geometry();
	_init_material();

	ProjectionMatrix = VzCore::Camera.get_projection_matrix();
	ModelMatrix = glm::translate(ModelMatrix, Position);
}

void VzVoxelBlockEntity::destroy() {
	glDeleteVertexArrays(1, &_vao);
	glDeleteBuffers(1, &_vbo);	
}

void VzVoxelBlockEntity::think() {
	ProjectionMatrix = VzCore::Camera.get_projection_matrix();
	ViewMatrix = VzCore::Camera.get_view_matrix();
}

void VzVoxelBlockEntity::render() {
	think();

	_shader->use();
	_shader->set_mat4("projection", ProjectionMatrix);
	_shader->set_mat4("view", ViewMatrix);
	_shader->set_mat4("model", ModelMatrix);
}

void VzVoxelBlockEntity::_init_shader() {
	auto vsFilePath = VzFileSystem::get_path("/resource/shader/voxel_block.vert");
	auto fsFilePath = VzFileSystem::get_path("/resource/shader/voxel_block.frag");
	bool isValid = !(vsFilePath.empty() || fsFilePath.empty());

	BOOST_ASSERT_MSG(isValid, "ERROR: SHADER FILE LOAD FAIL.");
	if (!isValid)
		return;

	_shader = std::make_unique<VzShader>(vsFilePath.c_str(), fsFilePath.c_str());
}

void VzVoxelBlockEntity::_init_geometry() {
}

void VzVoxelBlockEntity::_init_material() {
}
