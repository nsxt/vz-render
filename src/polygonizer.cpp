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

// TODO : polygonization 메소드에 각코너의 iso 값과, reuse 정점정보도 전달 하도록 하자.
void VzPolygonizer::polygonization(const VzCornerValue& V)
{
	auto case_code = get_case_code(V);
	const bool is_trival_case = ((case_code ^ ((V.D[7] >> 7) & 0xFF)) == 0);

	if (is_trival_case)
		return;

	using transvoxel::regularCellClass;
	using transvoxel::regularCellData;
	using transvoxel::RegularCellData;
	using transvoxel::regularVertexData;

	auto equivalence_class = regularCellClass[case_code];
	auto triangulation_case = regularCellData[equivalence_class];
	auto vertex_case = regularVertexData[case_code];

	auto triangle_vertex_size = triangulation_case.get_vertex_count();
	for (int vertex_index = 0; vertex_index < triangle_vertex_size; ++vertex_index) {
		
	}
}
