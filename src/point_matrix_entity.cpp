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

void VzPointMatrixEntity::create(const std::vector<char>& density, unsigned extent) {	
	generate_matrix(density, extent);
		
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
	glPointSize(10.0f);

	auto verticesSize = _vertices.size() * sizeof(float) * 3;
	glDrawArrays(GL_POINTS, 0, verticesSize);

	glPointSize(1.0f);
}

void VzPointMatrixEntity::destroy() {
	glDeleteVertexArrays(1, &_vao);
	glDeleteBuffers(1, &_vbo);
}

void VzPointMatrixEntity::think() {
	ProjectionMat = VzCore::Camera.get_projection_matrix();
	ViewMat = VzCore::Camera.get_view_matrix();
}

void VzPointMatrixEntity::generate_matrix(const std::vector<char>& density, unsigned extent) {
	assert(!density.empty());
	assert(extent > 1);

	if (std::pow(extent, 3) < 4)
		return;

	_vertices.clear();

	const char* isoMap = density.data();
	float weight = 1.0f;

	for (unsigned z = 0; z < extent; ++z)
		for (unsigned y = 0; y < extent; ++y)
			for (unsigned x = 0; x < extent; ++x) {
				unsigned index = x + (y * extent) + (z * extent * extent);
				if (isoMap[index] < 0) {
					_vertices.push_back( (glm::vec3(x, y, z) * weight));
				}
			}	
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
	
	auto verticesSize = _vertices.size() * sizeof(float) * 3;
	auto verticesDataPtr = _vertices.data();

	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);

	glBindVertexArray(_vao);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, verticesSize, verticesDataPtr, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void VzPointMatrixEntity::_init_material() {
}
