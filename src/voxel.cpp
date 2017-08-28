//---------------------------------------------------------
// Copyright (C) NSXTSoft. All rights reserved.

// ********************************************************
// File name : voxel.cpp
// Created   : 2017/08/28 by SungHoon Ko
// ********************************************************
//
///////////////////////////////////////////////////////////
#include "core.h"

VzVoxel::VzVoxel() {
}

VzVoxel::~VzVoxel() {
}

void VzVoxel::initialize() noexcept {
}

void VzVoxel::deinitialize() noexcept {
}

float VzVoxel::get_isovalue_sphere(int x, int y, int z) {
	float volume_size = static_cast<float>(VOXEL_EXTENT_PER_AXIS);
	float sphere_radius = 10.0f;
	return pow(x - volume_size / 2, 2) + pow(y - volume_size / 2, 2) + pow(z - volume_size / 2, 2) - pow(sphere_radius, 2);
}

void VzVoxel::create_block(const int& block_id) {
	const auto block_size = VOXEL_EXTENT_PER_AXIS * VOXEL_EXTENT_PER_AXIS * VOXEL_EXTENT_PER_AXIS;
	std::vector<Voxel> block_data(block_size);

	for (unsigned z = 0u; z < VOXEL_EXTENT_PER_AXIS; ++z)
		for (unsigned y = 0u; y < VOXEL_EXTENT_PER_AXIS; ++y)
			for (unsigned x = 0u; x < VOXEL_EXTENT_PER_AXIS; ++x) {
				block_data.clear();

				unsigned index = 0xffffffff;
				block_data[index].isovalue = get_isovalue_sphere(x, y, z);
			}
}

void VzVoxel::create_grid() {
	

}

void VzVoxel::push_block() {
}
