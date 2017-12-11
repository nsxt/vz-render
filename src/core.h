//---------------------------------------------------------
// Copyright (C) NSXTSoft. All rights reserved.

// ********************************************************
// File name : Core.h
// Created   : 2017/08/09 by SungHoon Ko
// ********************************************************
//
///////////////////////////////////////////////////////////
#pragma once

#define NOMINMAX
#define GLM_FORCE_LEFT_HANDED

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <array>
#include <chrono>
#include <map>
#include <unordered_map>
#include <memory>

#include <boost/assert.hpp>

#include "global.h"
#include "timer.h"
#include "file.h"
#include "shader.h"
#include "camera.h"
#include "color.h"
#include "font.h"
#include "ui.h"

#include "dummy_plane.h"
#include "dummy_cube.h"

#include "voxel_regular_table.h"
#include "voxel.h"
#include "voxel_block_entity.h"

#include "square_matrix_entity.h"
#include "point_matrix_entity.h"

// New Classes for re-factoring
#include "cube_entity.h"
#include "polygonizer.h"

//////////////////////////////////////////////////////
//
//	Application Module 
//

int init_app();
int deinit_app();
int run_app();

void clear_buffer();
void render_ui();

void init_dummy();
void render_dummy();
void destroy_dummy();


//////////////////////////////////////////////////////
//
//	Callbacks
//

void framebuffer_size_callback(GLFWwindow*, int, int);
void mouse_callback(GLFWwindow*, double, double);
void scroll_callback(GLFWwindow*, double, double);
void process_input(GLFWwindow*);


//////////////////////////////////////////////////////
//
//	Console function for test ans logging
//

void bind_console();
void unbind_console();
void stream_test();
void glm_test();
void print_vendor_info();

//////////////////////////////////////////////////////
//
//	Global shared variables
//

class VzCore {
public:
	static VzTimer Timer;
	static VzCamera Camera;
	static VzFont Font;
	static VzColor Color;	
	static VzUI UI;

	static VzDummyPlane DummyPlane;
	static VzDummyCube DummyCube;
		
	static VzVoxelBlockEntity VoxelBlockEntity;
	static VzSquareMatrixEntity SquareMatrixEntity;
	static VzPointMatrixEntity PointMatrixEntity;

	static VzPolygonizer Polygonizer;
};
