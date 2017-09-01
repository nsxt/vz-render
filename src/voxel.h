//---------------------------------------------------------
// Copyright (C) NSXTSoft. All rights reserved.

// ********************************************************
// File name : Voxel.h
// Created   : 2017/08/28 by SungHoon Ko
// ********************************************************
//
///////////////////////////////////////////////////////////
#pragma once

static const glm::vec3 UNIT_X = glm::vec3(1.f, 0.f, 0.f);
static const glm::vec3 UNIT_Y = glm::vec3(0.f, 1.f, 0.f);
static const glm::vec3 UNIT_Z = glm::vec3(0.f, 0.f, 1.f);

class VzVoxel {
public:
	static constexpr unsigned BLOCK_EXTENT = 16u;
	static constexpr unsigned GRID_EXTENT = 1u;

public:
	VzVoxel();
	~VzVoxel();

public:
	enum class BlockFlags : unsigned short {
		VZ_BF_Empty = 0,
		VZ_BF_OK = 1 << 0,
		VZ_BF_Compressed = 1 << 1,
		VZ_BF_Dirty = 0xffff
	};

	struct Block {
		Block() 
			: id(0), flags(BlockFlags::VZ_BF_Empty) {}

		Block(Block&& rhs)
			: id(rhs.id)
			, flags(rhs.flags)
			, pos(rhs.pos)
			, voxel_data(std::move(rhs.voxel_data)) {}

		unsigned id;
		BlockFlags flags;
		glm::vec3 pos;
		std::vector<char> voxel_data;
	};

	struct Cell {
		glm::vec3 Pos;
		glm::vec3 LocalPos;
		char Corner[8];
	};

public:
	void initialize() noexcept;
	void deinitialize() noexcept;

	void create_block(const int& block_id);
	void create_grid();
	void push_block();

	float get_isovalue_sphere(int x, int y, int z);

	void polygonize_block();

	Cell make_cell(const Block& block_, const glm::vec3& localPos_);

	glm::vec3 get_local_corner_pos(int cornerId, const glm::vec3& cellLocalPos);

	char get_voxel_value(const glm::vec3& cornerPos, const Block& block);
	
	unsigned get_voxel_map_index(const glm::vec3& pos) const;

	unsigned get_case_code(const char v[8]);
	
private:
	std::vector<Block> _blocks;
};
