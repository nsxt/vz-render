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

void VzVoxel::create_block(const int& blockId) {
	const auto block_size = BLOCK_EXTENT * BLOCK_EXTENT * BLOCK_EXTENT;

	Block block;
	block.ID = blockId;
	block.Flags = BlockFlags::VZ_BF_OK;
	block.Pos = glm::vec3();
	block.Density.resize(block_size);
	block.Density.clear();

	for (unsigned z = 0u; z < BLOCK_EXTENT; ++z)
		for (unsigned y = 0u; y < BLOCK_EXTENT; ++y)
			for (unsigned x = 0u; x < BLOCK_EXTENT; ++x) {
				unsigned index = x + (y * BLOCK_EXTENT) + (z * BLOCK_EXTENT * BLOCK_EXTENT);
				block.Density[index] = get_isovalue_sphere(x, y, z) > 0 ? 0 : 0xFF;
			}

	_blocks.push_back(std::move(block));
}

void VzVoxel::create_grid() {
	create_block(0);
}

void VzVoxel::push_block() {
}

void VzVoxel::polygonize_block() {

	Block& block = _blocks.back();

	unsigned determineVertIndices[15];
	unsigned char reuseValidityMask = 0;

	for (unsigned cell_z = 0; cell_z < BLOCK_EXTENT; ++cell_z) {
		// clear the y-bit
		reuseValidityMask &= 0xD;

		for (unsigned cell_y = 0; cell_y < BLOCK_EXTENT; ++cell_y) {
			// clear the x-bit
			reuseValidityMask &= 0xE;

			for (unsigned cell_x = 0; cell_x < BLOCK_EXTENT; ++cell_x) {

				glm::vec3 cellLocalPos(cell_x, cell_y, cell_z);
				Cell cell = make_cell(block, cellLocalPos);
				
				// classify the equivalence class indec for a cell
				const unsigned caseCode = get_case_code(cell.V);

				// if the case index is either 0 or 255, then the cell contains no triangles.
				const bool isTrivial = ((caseCode ^ ((cell.V[7] >> 7) & 0xFF)) == 0);
				if (isTrivial)
					continue;

				const unsigned regCellClass = VzVoxelRegularTable::regularCellClass[caseCode];
				const VzVoxelRegularTable::RegularCellData regCellData = VzVoxelRegularTable::regularCellData[regCellClass];
				const unsigned short* regVertexData = VzVoxelRegularTable::regularVertexData[caseCode];

				auto regVertSize = regCellData.get_vertex_count();
				for (long curRegVertCount = 0; curRegVertCount < regVertSize; ++curRegVertCount) {

					// the low byte of 16-bit code contains the corner indexes of the edge's endpoints -
					// in one nibble each. ex) 0x2315 is corners 1 and 5.
					const char edgeIndex = regVertexData[curRegVertCount] & 0xFF;

					// the high nibble of this code indicates which direction to go
					// in order to reach the correct preceeding cell.
					char direction = (regVertexData[curRegVertCount] >> 12);

					// the low nibble of the 8-bit code gives the index of the vertex in the preceeding cell
					// that should be reused or index of the vertex in the current cell that should be created.
					char vertIndexInCell = (regVertexData[curRegVertCount] >> 8) & 0x0F;

					bool isReuse = true;
					bool shouldCreateNewVertex = true;

					const unsigned char V0 = (edgeIndex >> 4) & 0x0F;
					const unsigned char V1 = edgeIndex & 0x0F;
					long t = (cell.V[V1] << 8) / (cell.V[V1] - cell.V[V0]);

					// the vertex lies on endpoint of the edge
					if ((t & 0x00FF) == 0) {
						// vertex lies at the higher-numbered endpoint. we never reuse.
						if (t == 0 && V1 == 7)
							isReuse = false;

						// vertex lies on endpoint of the edge.
						// we need to modify the direction.
						if (isReuse) {
							auto dirModifier = (t == 0) ? V1 : V0;
							direction = (dirModifier ^ 7);
						}

						// override the reuse index when a vertex lies on an edge endpoint.
						vertIndexInCell = 0;
					}

					// reuse an old vertex
					if ((direction & reuseValidityMask) == direction && isReuse) {
						glm::vec3 reuseCellPos = get_pos_adjcell(direction, cellLocalPos);
						auto reuseVertexID = make_id_reuse_vertex(reuseCellPos);

						auto it_reuseVertInfo = block.ReuseVertices.find(reuseVertexID);
						if (it_reuseVertInfo != block.ReuseVertices.end()) {
							auto reuseVertInfo = it_reuseVertInfo->second;
							auto reuseIndex = reuseVertInfo.VertexIndices[vertIndexInCell];

							// it is assumed that cell's material and reuse material are the same.
							determineVertIndices[curRegVertCount] = reuseIndex;

							// vertex lie on the interior of an edge, so that they must have vertex index.
							if ((t & 0x00FF) != 0 && t != 0) {
								BOOST_ASSERT(determineVertIndices[curRegVertCount] != INVALID_INDEX);
							}
							else {
								if (determineVertIndices[curRegVertCount] == INVALID_INDEX) {
									// we allow the creation of a vertex here (it's the lower endpoint of an edge)
									auto index = generate_vertex_from_point(block, cell, V0);
									determineVertIndices[curRegVertCount] = index;
								}
							}
						}
						else {
							BOOST_ASSERT_MSG(0, "No data to reuse vertex in block.");
						}

						shouldCreateNewVertex = false;
					}

					// create a new vertex on this position
					if (shouldCreateNewVertex) {
						// vertex lies on one of the endpoints - create the new vertex there
						if ((t & 0x00FF) == 0) {
							auto index = generate_vertex_from_point(block, cell, (t == 0) ? V1 : V0);

							if (t == 0 && V1 == 7) {
								Block::ReuseVertexInfo reuseInfo;
								reuseInfo.VertexIndices[vertIndexInCell] = index;	
								auto reuseId = make_id_reuse_vertex(cell.LocalPos);

								block.ReuseVertices.emplace(std::make_pair(reuseId, std::move(reuseInfo)));

								// save this index for the triangulation
								determineVertIndices[curRegVertCount] = index;
							}
						}
						// vertex lies in the interior of the edge.
						else {
							auto P0 = get_pos_corner(V0, cell.Pos);
							auto P1 = get_pos_corner(V1, cell.Pos);

							const long u = 0x0100 - t;
							glm::vec4 Q = glm::vec4((float)t * P0 + (float)u * P1, 0.0f);

							block.Vertices.push_back(Q);
							auto index = block.Vertices.size() - 1;

							// save the index in this cell's reuse data
							if (direction == 0x8) {
								Block::ReuseVertexInfo reuseInfo;
								reuseInfo.VertexIndices[vertIndexInCell] = index;
								auto reuseId = make_id_reuse_vertex(cell.LocalPos);
								block.ReuseVertices.emplace(std::make_pair(reuseId, std::move(reuseInfo)));
							}

							// save this index for the triangulation
							determineVertIndices[curRegVertCount] = index;
						}
					}

					// push all triangles
					auto triMaxCount = regCellData.get_triangle_count() * 3;
					for (auto triCount = 0L; triCount < triMaxCount; triCount += 3) {
						for (auto vert = 0; vert < 3; ++vert) {
							auto regIndex = regCellData.vertex_index[triCount + vert];
							auto resultIndex = determineVertIndices[regIndex];
							block.Indices.push_back(resultIndex);
						}
					}
				}
				
				reuseValidityMask |= 0x1;
			} // Loop's Cell_X

			if (reuseValidityMask & 1)
				reuseValidityMask |= 0x2;
		} // Loop's Cell_Y

		if (reuseValidityMask & 2)
			reuseValidityMask |= 0x4;
	} // Loop's Cell_Z

}

VzVoxel::Cell VzVoxel::make_cell(const Block& block, const glm::vec3& localPos) {	
	Cell cell;

	cell.Pos = glm::vec3(
		(localPos.x + block.Pos.x * BLOCK_EXTENT),
		(localPos.y + block.Pos.y * BLOCK_EXTENT),
		(localPos.z + block.Pos.z * BLOCK_EXTENT)
	);

	cell.LocalPos = localPos;

	for (auto i = 0; i < 8; ++i) {
		auto cornerPos = get_pos_corner(i, localPos);
		char d = get_density(cornerPos, block);
		cell.V[i] = d;
	}
	
	return cell;
}

glm::vec3 VzVoxel::get_pos_corner(int cornerId, const glm::vec3& basePos) {
	switch (cornerId) {
	case 0 : 
		return basePos;
	case 1 :
		return basePos + UNIT_X;
	case 2 :
		return basePos - UNIT_Z;
	case 3 :
		return basePos + UNIT_X - UNIT_Z;
	case 4 :
		return basePos + UNIT_Y;
	case 5 :
		return basePos + UNIT_X + UNIT_Y;
	case 6 :
		return basePos + UNIT_Y - UNIT_Z;
	case 7 :
		return basePos + UNIT_X + UNIT_Y - UNIT_Z;
	}

	return glm::vec3(FLT_MAX);
}

char VzVoxel::get_density(const glm::vec3& cornerPos, const Block& block) {
	auto index = get_index_density_map(cornerPos);
	return block.Density[index];
}

unsigned VzVoxel::get_index_density_map(const glm::vec3 & pos) const {
	return static_cast<unsigned>(pos.x + (pos.y * BLOCK_EXTENT) + (pos.z * BLOCK_EXTENT * BLOCK_EXTENT));
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

glm::vec3 VzVoxel::get_pos_adjcell(const char direction, const glm::vec3 & cellPos) {
	auto adjCellPos(cellPos);
	
	if (direction & 0x1) {
		adjCellPos.x -= 1.0f;
	}
	if (direction & 0x2) {
		adjCellPos.y -= 1.0f;
	}
	if (direction & 0x4) {
		adjCellPos.z -= 1.0f;
	}

	return adjCellPos;
}

unsigned VzVoxel::make_id_reuse_vertex(const glm::vec3 & reusePos) {
	return static_cast<unsigned>(reusePos.x + (reusePos.y * BLOCK_EXTENT) + (reusePos.z * BLOCK_EXTENT * BLOCK_EXTENT));
}

unsigned VzVoxel::generate_vertex_from_point(Block& block, const Cell& cell, char cornerId) {
	auto V = get_pos_corner(cornerId, cell.Pos);

	// todo : calculate normal and process material info.
	V *= 256.0f;
	block.Vertices.push_back(glm::vec4(V, 0.0f));

	return block.Vertices.size() - 1;
}
