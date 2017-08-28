//---------------------------------------------------------
// Copyright (C) NSXTSoft. All rights reserved.

// ********************************************************
// File name : Voxel.h
// Created   : 2017/08/28 by SungHoon Ko
// ********************************************************
//
///////////////////////////////////////////////////////////
#pragma once

class VzVoxel {
public:
	static constexpr unsigned VOXEL_EXTENT_PER_AXIS = 16u;
	static constexpr unsigned BLOCK_EXTENT_PER_GRID_AXIS = 4u;

public:
	VzVoxel();
	~VzVoxel();

public:
	enum class BlockFlags : unsigned short {
		VBF_Empty = 0,
		VBF_OK = 1 << 0,
		VBF_Compressed = 1 << 1,
		VBF_Dirty = 0xffff
	};

	struct Voxel {
		float isovalue;
	};

	struct Block {
		Block() 
			: id(0), flags(BlockFlags::VBF_Empty) {}

		Block(Block&& rhs)
			: id(rhs.id)
			, flags(rhs.flags)
			, voxel_data(std::move(rhs.voxel_data)) {}

		unsigned id;
		BlockFlags flags;
		std::vector<Voxel> voxel_data;
	};

public:
	void initialize() noexcept;
	void deinitialize() noexcept;

	void create_block(const int& block_id);
	void create_grid();
	void push_block();

	float get_isovalue_sphere(int x, int y, int z);

private:
	std::vector<Block> m_Blocks;
};
