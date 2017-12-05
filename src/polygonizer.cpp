#include "core.h"

const unsigned VzPolygonizer::get_case_code(const VzCornerValue& V)
{
	return	((V.D[0] >> 7) & 0x01) | 
			((V.D[1] >> 6) & 0x02) |
			((V.D[2] >> 5) & 0x04) |
			((V.D[3] >> 4) & 0x08) |
			((V.D[4] >> 3) & 0x10) |
			((V.D[5] >> 2) & 0x20) |
			((V.D[6] >> 1) & 0x40) |
			(V.D[7] & 0x80);

}

void VzPolygonizer::polygonization(const VzCornerValue& V, VzCell& cell)
{
	using transvoxel::regularCellClass;
	using transvoxel::regularCellData;
	using transvoxel::RegularCellData;
	using transvoxel::regularVertexData;

	auto case_code = get_case_code(V);
	const bool is_trival_case = ((case_code ^ ((V.D[7] >> 7) & 0xFF)) == 0);

	if (is_trival_case)
		return;

	std::array<unsigned, 15> created_vertex_index;

	// Marching Cubes case index to an equivalence class index
	auto equivalence_class = regularCellClass[case_code];
	// Triangulation data for all 16 distinct classes
	auto triangulation_class = regularCellData[equivalence_class];
	// Vertex locations for every one of the 256 possible cases in modified Marching Cubes
	auto vertex_class = regularVertexData[case_code];

	auto triangle_vertex_size = triangulation_class.get_vertex_count();
	for (int count=0; count < triangle_vertex_size; ++count) {

		// direction to the correct preceding cell. ex) 0x2315 is direction 2
		char preceding_cell_dir = (vertex_class[count] >> 12);

		// index of vertex to the new or reused vertex. ex) 0x2315 is vertex index 3
		char reuse_vertex_index = (vertex_class[count] >> 8) & 0x0F;

		// corner indexes of the edge's endpoints. ex) 0x2315 is corners 1 and 5
		const unsigned char edge_class = vertex_class[count] & 0xFF;
		const unsigned char corner_0 = (edge_class >> 4) & 0x0F;
		const unsigned char corner_1 = edge_class & 0x0F;

		const char d0 = V.D[corner_0];
		const char d1 = V.D[corner_1];
		const short t = (d1 - d0) != 0 ? (d1 << 8) / (d1 - d0) : (d1 << 8);

		// vertex lies in the interior of the edge.
		if ((t & 0x00FF) != 0) {
			auto P0 = V.P[corner_0];
			auto P1 = V.P[corner_1];

			const short u = 0x0100 - t;
			glm::vec4 Q = glm::vec4((float)t * P0 + (float)u * P1, 0.0f);
			Q *= (1.0f / 256.0f);

			cell.vertices.push_back(Q);
			created_vertex_index[count] = cell.vertices.size() - 1;
		}
		// vertex lies at the higher-numbered endpoint.
		else if (t == 0) {

			// this cell owns the verex.
			if (corner_1 == 7) {

			}
			// try to reuse corner vertex from a preceding cell.
			else {

			}

		}
		// vertex lies at the lower-numbered endpoint.
		// always try to reuse corner vertex from a preceding cell.
		else {

		}

	} // end of vertex counting loop.

	// make vertex index for the triangulation.
	auto triangle_size = triangulation_class.get_triangle_count();
	for (auto tri = 0; tri < triangle_size; ++tri) {
		for (auto vert = 0; vert < 3; ++vert) {
			auto index = triangulation_class.vertex_index[tri + vert];
			auto result = created_vertex_index[index];
			cell.indicies.push_back(result);
		}
	}
}
