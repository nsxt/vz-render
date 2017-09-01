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
	float volume_size = static_cast<float>(BLOCK_EXTENT);
	float sphere_radius = 10.0f;
	return pow(x - volume_size / 2, 2) + pow(y - volume_size / 2, 2) + pow(z - volume_size / 2, 2) - pow(sphere_radius, 2);
}

void VzVoxel::create_block(const int& blockId_) {
	const auto block_size = BLOCK_EXTENT * BLOCK_EXTENT * BLOCK_EXTENT;

	Block new_block;
	new_block.id = blockId_;
	new_block.flags = BlockFlags::VZ_BF_OK;
	new_block.pos = glm::vec3();
	new_block.voxel_data.resize(block_size);
	new_block.voxel_data.clear();

	for (unsigned z = 0u; z < BLOCK_EXTENT; ++z)
		for (unsigned y = 0u; y < BLOCK_EXTENT; ++y)
			for (unsigned x = 0u; x < BLOCK_EXTENT; ++x) {
				unsigned index = x + (y * BLOCK_EXTENT) + (z * BLOCK_EXTENT * BLOCK_EXTENT);
				new_block.voxel_data[index] = get_isovalue_sphere(x, y, z) > 0 ? 0 : 0xff;
			}

	_blocks.push_back(std::move(new_block));
}

void VzVoxel::create_grid() {
	create_block(0);
}

void VzVoxel::push_block() {
}

void VzVoxel::polygonize_block() {

	const Block& block = _blocks.back();

	for (unsigned cell_z = 0; cell_z < BLOCK_EXTENT; ++cell_z) {
		for (unsigned cell_y = 0; cell_y < BLOCK_EXTENT; ++cell_y) {
			for (unsigned cell_x = 0; cell_x < BLOCK_EXTENT; ++cell_x) {

				glm::vec3 cellLocalPos(cell_x, cell_y, cell_z);
				Cell cell = make_cell(block, cellLocalPos);
				
				// classify the equivalence class indec for a cell
				const unsigned caseCode = get_case_code(cell.Corner);

				// if the case index is either 0 or 255, then the cell contains no triangles.
				const bool isTrivial = ((caseCode ^ ((cell.Corner[7] >> 7) & 0xFF)) == 0);
				if (isTrivial)
					continue;

				const unsigned cellClassIndex = VzVoxelRegularTable::regularCellClass[caseCode];
				const VzVoxelRegularTable::RegularCellData regCellData = VzVoxelRegularTable::regularCellData[cellClassIndex];
				const unsigned short* regVertexData = VzVoxelRegularTable::regularVertexData[caseCode];

			} // Loop's Cell_X

		} // Loop's Cell_Y

	} // Loop's Cell_Z

}

VzVoxel::Cell VzVoxel::make_cell(const Block& block, const glm::vec3& localPos) {	
	Cell cell;

	cell.Pos = glm::vec3(
		(localPos.x + block.pos.x * BLOCK_EXTENT),
		(localPos.y + block.pos.y * BLOCK_EXTENT),
		(localPos.z + block.pos.z * BLOCK_EXTENT)
	);

	cell.LocalPos = localPos;

	for (auto i = 0; i < 8; ++i) {
		auto cornerPos = get_local_corner_pos(i, localPos);
		char value = get_voxel_value(cornerPos, block);
		cell.Corner[i] = value;
	}
	
	return cell;
}

glm::vec3 VzVoxel::get_local_corner_pos(int cornerId, const glm::vec3& cellLocalPos) {	
	switch (cornerId) {
	case 0 : 
		return cellLocalPos;
	case 1 :
		return cellLocalPos + UNIT_X;
	case 2 :
		return cellLocalPos - UNIT_Z;
	case 3 :
		return cellLocalPos + UNIT_X - UNIT_Z;
	case 4 :
		return cellLocalPos + UNIT_Y;
	case 5 :
		return cellLocalPos + UNIT_X + UNIT_Y;
	case 6 :
		return cellLocalPos + UNIT_Y - UNIT_Z;
	case 7 :
		return cellLocalPos + UNIT_X + UNIT_Y - UNIT_Z;
	}

	return glm::vec3(FLT_MAX);
}

char VzVoxel::get_voxel_value(const glm::vec3& cornerPos, const Block& block) {
	auto index = get_voxel_map_index(cornerPos);
	return block.voxel_data[index];
}

unsigned VzVoxel::get_voxel_map_index(const glm::vec3 & pos) const {
	return pos.x + (pos.y * BLOCK_EXTENT) + (pos.z * BLOCK_EXTENT * BLOCK_EXTENT);
}

unsigned VzVoxel::get_case_code(const char v[8]) {
	return	((v[0] >> 7) & 0x01)
		  | ((v[1] >> 6) & 0x02)
		  | ((v[2] >> 5) & 0x04)
		  | ((v[3] >> 4) & 0x08)
		  | ((v[4] >> 3) & 0x10)
		  | ((v[5] >> 2) & 0x20)
		  | ((v[6] >> 1) & 0x40)
		  |  (v[7] & 0x80);
}
