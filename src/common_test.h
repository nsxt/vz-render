#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>

#include <iostream>

void bind_console();
void unbind_console();

void stream_test();
void glm_test();

void framebuffer_size_callback(GLFWwindow*, int, int);
void process_input(GLFWwindow*);
int run_app();
