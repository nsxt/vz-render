//////////////////////////////////////////////////////
//----------------------------------------------------
/*

	something title....

*/
//----------------------------------------------------
//////////////////////////////////////////////////////
#pragma once

#define NOMINMAX

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <chrono>

#include "global.h"
#include "timer.h"
#include "file.h"
#include "shader.h"
#include "camera.h"
#include "plane.h"
#include "cube.h"


//////////////////////////////////////////////////////
//
//	Application Module 
//

int init_app();
int run_app();

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

//////////////////////////////////////////////////////
//
//	Global shared variables
//

class VzCore {
public:
	static VzTimer Timer;
	static VzCamera Camera;
	static VzPlane Plane;
	static VzCube Cube;	
};
