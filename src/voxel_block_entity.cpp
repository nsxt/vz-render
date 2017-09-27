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
	
	_voxel = std::make_unique<VzVoxel>();
	_voxel->initialize();

	_init_shader();
	_init_geometry();
	_init_material();

	ProjectionMatrix = VzCore::Camera.get_projection_matrix();
	ModelMatrix = glm::translate(ModelMatrix, Position);
}

void VzVoxelBlockEntity::destroy() {
	glDeleteVertexArrays(1, &_vao);
	glDeleteBuffers(1, &_vbo);
	glDeleteBuffers(1, &_ebo);
}

void VzVoxelBlockEntity::think() {
	ProjectionMatrix = VzCore::Camera.get_projection_matrix();
	ViewMatrix = VzCore::Camera.get_view_matrix();
}

const std::vector<char>& VzVoxelBlockEntity::get_block_density() const {
	return _voxel->get_block_density();
}

void VzVoxelBlockEntity::render() {
	think();

	_shader->use();
	_shader->set_mat4("projection", ProjectionMatrix);
	_shader->set_mat4("view", ViewMatrix);
	_shader->set_mat4("model", ModelMatrix);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth((GLfloat)3.0f);

	glBindVertexArray(_vao);
	glDrawElements(GL_TRIANGLES, _voxel->get_block_indices_size(), GL_UNSIGNED_INT, 0);	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glLineWidth((GLfloat)1.0f);
}

void VzVoxelBlockEntity::_init_shader() {
	auto vsFilePath = VzFileSystem::get_path("/resource/shaders/voxel_block.vert");
	auto fsFilePath = VzFileSystem::get_path("/resource/shaders/voxel_block.frag");
	bool isValid = !(vsFilePath.empty() || fsFilePath.empty());

	BOOST_ASSERT_MSG(isValid, "ERROR: SHADER FILE LOAD FAIL.");
	if (!isValid)
		return;

	_shader = std::make_unique<VzShader>(vsFilePath.c_str(), fsFilePath.c_str());
}

float vertices[] = {
	1.0f,  0.0f, 0.0f,
	0.0f,  1.0f, 0.0f,
	0.0f,  0.0f, 1.0f,
};
unsigned int indices[] = {  // note that we start from 0!
	0, 1, 2,  // first Triangle	
};

void VzVoxelBlockEntity::_init_geometry() {
	const unsigned blockVerticesSize = _voxel->get_block_vertices_size();
	const unsigned blockIndicesSize = _voxel->get_block_indices_size();

	if (blockVerticesSize == 0 || blockIndicesSize == 0)
		return;
	
	auto blockVertices = _voxel->get_block_vertices();
	auto blockIndicies = _voxel->get_block_indices();
	
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	glGenBuffers(1, &_ebo);

	// bind the Vertex Array Object first, then bind and set vertex buffer(s),
	// and then configure vertex attributes(s).
	glBindVertexArray(_vao);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * blockVerticesSize * 3, blockVertices, GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned) * blockIndicesSize, blockIndicies, GL_STATIC_DRAW);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound
	// vertex buffer object so afterwards we can safely unbind.
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// NB : do NOT unbind the EBO while a VAO is active as the bound element buffer objects IS stored in the VAO; keep the EBO bound.
	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// you can unbind the VAO afterward so other VAO calls won't accidentally modify this VAO, but this rarely happens. 
	// Modifying other VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs)
	// when is's not directly necessary.
	glBindVertexArray(0);
}

void VzVoxelBlockEntity::_init_material() {
}
