#include "core.h"

void VzCubeRenderer::init()
{
}

void VzCubeRenderer::render()
{
}

void VzCubeRenderer::deinit()
{
}

void VzCubeRenderer::setup_cube(const VzCubeCreateInfo & info)
{
	assert(info.dim_x > 0);
	assert(info.dim_y > 0);
	assert(info.dim_z > 0);
	assert(info.len_weight > 0.0f);

	created_info = info;

	////////////////////////////////////////////////////////////
	// create vertex
	for (int y = 0; y < info.dim_y + 1; ++y)
		for (int z = 0; z < info.dim_z + 1; ++z)
			for (int x = 0; x < info.dim_x + 1; ++x) {
				glm::vec3 pos((float)x, (float)y, (float)z);
				pos *= info.len_weight;
				pos += info.start_pos;
				vertices.push_back(pos);
			}

	////////////////////////////////////////////////////////////
	// axis-x line	
	for (int y = 0; y < info.dim_y + 1; ++y)
		for (int z = 0; z < info.dim_z + 1; ++z) {
			int start_index = (z * info.dim_x) + z;
			int end_index = (z * info.dim_x) + z + info.dim_x;
			start_index += y * (info.dim_x + 1) * (info.dim_z + 1);
			end_index += y * (info.dim_x + 1) * (info.dim_z + 1);
		}

	////////////////////////////////////////////////////////////
	// axis-y line	


	////////////////////////////////////////////////////////////
	// axis-z line	
}
