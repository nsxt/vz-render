//---------------------------------------------------------
// Copyright (C) NSXTSoft. All rights reserved.

// ********************************************************
// File name : Core.cpp
// Created   : 2017/08/09 by SungHoon Ko
// ********************************************************
//
///////////////////////////////////////////////////////////
#include "core.h"

VzTimer VzCore::Timer;
VzCamera VzCore::Camera;
VzColor VzCore::Color;
VzFont VzCore::Font;
VzPlane VzCore::Plane(glm::vec3(0.0f, 0.0f, 0.0f));
VzCube VzCore::Cube(glm::vec3(0.0f, 0.0f, 0.0f));
VzVoxelBlockEntity VzCore::VoxelBlockEntity;
