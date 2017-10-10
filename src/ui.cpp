//---------------------------------------------------------
// Copyright (C) NSXTSoft. All rights reserved.

// ********************************************************
// File name : ui.cpp
// Created   : 2017/10/10 by SungHoon Ko
// ********************************************************
//
///////////////////////////////////////////////////////////
#include "core.h"

VzUI::VzUI() :
	_is_show_fixed_overay{ true }, _is_show_debug_property{ true } {
}

VzUI::~VzUI() {
}

void VzUI::think() {
	ImGui_ImplGlfwGL3_NewFrame();

	show_debug_property();
	show_fixed_overay();

	ImGui::Render();
}

void VzUI::show_fixed_overay() {
	ImGui::SetNextWindowPos(ImVec2(10, 10));
	if (!ImGui::Begin("Fixed Overlay", &_is_show_fixed_overay, ImVec2(0, 0), 0.3f,
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_AlwaysAutoResize ))
	{
		ImGui::End();
		return;
	}
	
	ImGui::Text("Mouse Position: (%.1f,%.1f)", ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y);
	ImGui::Separator();

	const glm::vec3& cam = VzCore::Camera.Position;
	ImGui::Text("Camera Position (%.1f,%.1f,%.1f)", cam.x, cam.y, cam.z);
	ImGui::Separator();

	ImGui::Text("FPS %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	ImGui::End();
}

void VzUI::show_debug_property() {	
	if (!ImGui::Begin("VZ-Render Property", &_is_show_debug_property)) {
		ImGui::End();
		return;
	}
	ImGui::End();
}
