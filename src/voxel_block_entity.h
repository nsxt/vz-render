//---------------------------------------------------------
// Copyright (C) NSXTSoft. All rights reserved.

// ********************************************************
// File name : voxel_block_entity.h
// Created   : 2017/09/07 by SungHoon Ko
// ********************************************************
//
///////////////////////////////////////////////////////////
#pragma once

class VzVoxelBlockEntity {
public:
	glm::vec3 Position;
	glm::vec3 Orientation;
	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;
	glm::mat4 ModelMatrix;

public:	
	VzVoxelBlockEntity();
	~VzVoxelBlockEntity();

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
	std::unique_ptr<VzVoxel> _voxel;
	std::unique_ptr<VzShader> _shader;
	GLuint _vbo;
	GLuint _ebo;
	GLuint _vao;
};
