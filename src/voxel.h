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
	static constexpr unsigned INVALID_INDEX = 0xFFFFFFFF;
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

	template<unsigned Size>
	struct GenericReuseVertexInfo {
		ReuseVertexInfo() { 
			reset(); 
		}

		void reset() {
			std::fill(VertexIndices, VertexIndices + Size, INVALID_INDEX);
		}

		unsigned VertexIndices[Size];
	};

	struct Block {
		Block() 
			: ID(0)
			, Flags(BlockFlags::VZ_BF_Empty) {}

		Block(Block&& rhs)
			: ID(rhs.ID)
			, Flags(rhs.Flags)
			, Pos(rhs.Pos)
			, Density(std::move(rhs.Density))
			, Vertices(std::move(rhs.Vertices))
			, ReuseVertices(std::move(rhs.ReuseVertices)) {}

		unsigned ID;
		BlockFlags Flags;
		glm::vec3 Pos;
		std::vector<char> Density;
		std::vector<glm::vec4> Vertices;

		typedef GenericReuseVertexInfo<4> ReuseVertexInfo;
		std::unordered_map<unsigned, ReuseVertexInfo> ReuseVertices;
	};

	struct Cell {
		glm::vec3 Pos;
		glm::vec3 LocalPos;
		char V[8];
	};

public:
	void initialize() noexcept;
	void deinitialize() noexcept;

	void create_block(const int& block_id);
	void create_grid();
	void push_block();

	float get_isovalue_sphere(int x, int y, int z);

	void polygonize_block();

	Cell make_cell(const Block& block, const glm::vec3& localPos);

	glm::vec3 get_pos_corner(int cornerId, const glm::vec3& cellPos);

	char get_density(const glm::vec3& cornerPos, const Block& block);
	
	unsigned get_index_density_map(const glm::vec3& pos) const;

	unsigned get_case_code(const char v[8]);

	glm::vec3 get_pos_adjcell(const char direction, const glm::vec3& cellPos);

	unsigned make_id_reuse_vertex(const glm::vec3& reusePos);
	
private:
	std::vector<Block> _blocks;
};
