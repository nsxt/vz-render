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
VzColor VzCore::Color;
VzFont VzCore::Font;
VzDummyPlane VzCore::DummyPlane(glm::vec3(0.0f, 0.0f, 0.0f));
VzDummyCube VzCore::DummyCube(glm::vec3(0.0f, 0.0f, 0.0f));
VzUI VzCore::UI;

VzVoxelBlockEntity VzCore::VoxelBlockEntity;
VzSquareMatrixEntity VzCore::SquareMatrixEntity;
VzPointMatrixEntity VzCore::PointMatrixEntity;

VzPolygonizer VzCore::Polygonizer;
