//---------------------------------------------------------
// Copyright (C) NSXTSoft. All rights reserved.

// ********************************************************
// File name : voxel_regular_table.h
// Created   : 2017/08/21 by SungHoon Ko
// ********************************************************
//
// The following data originates from Eric Lengyel's Transvoxel Algorithm.
// http://transvoxel.org/
//
///////////////////////////////////////////////////////////
#pragma once

class VzVoxelRegularTable {
public:
	// The RegularCellData structure holds information about the triangulation
	// used for a single equivalence class in the modified Marching Cubes algorithm,
	// described in Section 3.2.
	struct RegularCellData {
		unsigned char	geometry_counts;	// High nibble is vertex count, low nibble is triangle count.
		unsigned char	vertex_index[15];	// Groups of 3 indexes giving the triangulation.

		long get_vertex_count(void) const {
			return (geometry_counts >> 4);
		}

		long get_triangle_count(void) const {
			return (geometry_counts & 0x0F);
		}
	};

	// The TransitionCellData structure holds information about the triangulation
	// used for a single equivalence class in the Transvoxel Algorithm transition cell,
	// described in Section 4.3.
	struct TransitionCellData {
		long			geometry_counts;	// High nibble is vertex count, low nibble is triangle count.
		unsigned char	vertex_index[36];	// Groups of 3 indexes giving the triangulation.

		long get_vertex_count(void) const {
			return (geometry_counts >> 4);
		}

		long get_triangle_count(void) const {
			return (geometry_counts & 0x0F);
		}
	};

public:
	// The regularCellClass table maps an 8-bit regular Marching Cubes case index to
	// an equivalence class index. Even though there are 18 equivalence classes in our
	// modified Marching Cubes algorithm, a couple of them use the same exact triangulations,
	// just with different vertex locations. We combined those classes for this table so
	// that the class index ranges from 0 to 15.
	static const unsigned char regularCellClass[256];	

	// The regularCellData table holds the triangulation data for all 16 distinct classes to
	// which a case can be mapped by the regularCellClass table.
	static const RegularCellData regularCellData[16];

	// The regularVertexData table gives the vertex locations for every one of the 256 possible
	// cases in the modified Marching Cubes algorithm. Each 16-bit value also provides information
	// about whether a vertex can be reused from a neighboring cell. See Section 3.3 for details.
	// The low byte contains the indexes for the two endpoints of the edge on which the vertex lies,
	// as numbered in Figure 3.7. The high byte contains the vertex reuse data shown in Figure 3.8.
	static const unsigned short regularVertexData[256][12];

	// The transitionCellClass table maps a 9-bit transition cell case index to an equivalence
	// class index. Even though there are 73 equivalence classes in the Transvoxel Algorithm,
	// several of them use the same exact triangulations, just with different vertex locations.
	// We combined those classes for this table so that the class index ranges from 0 to 55.
	// The high bit is set in the cases for which the inverse state of the voxel data maps to
	// the equivalence class, meaning that the winding order of each triangle should be reversed.
	static const unsigned char transitionCellClass[512];
	
	// The transitionCellData table holds the triangulation data for all 56 distinct classes to
	// which a case can be mapped by the transitionCellClass table. The class index should be ANDed
	// with 0x7F before using it to look up triangulation data in this table.
	static const TransitionCellData transitionCellData[56];

	// The transitionCornerData table contains the transition cell corner reuse data
	// shown in Figure 4.18.
	static const unsigned char transitionCornerData[13];

	// The transitionVertexData table gives the vertex locations for every one of the 512 possible
	// cases in the Tranvoxel Algorithm. Each 16-bit value also provides information about whether
	// a vertex can be reused from a neighboring cell. See Section 4.5 for details. The low byte
	// contains the indexes for the two endpoints of the edge on which the vertex lies, as numbered
	// in Figure 4.16. The high byte contains the vertex reuse data shown in Figure 4.17.
	static const unsigned short transitionVertexData[512][12];
};