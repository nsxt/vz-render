#include "core.h"
#include <glm/gtc/type_ptr.hpp>

void VzCubeEntity::init()
{
	VzCubeCreateInfo cube = { glm::vec3(0.0f), 1, 2, 1, 1.0f };
	setup_cube(cube);

	// initialize shader
	auto vs_file = VzFileSystem::get_path("/resource/shaders/square_matrix.vert");
	auto ps_file = VzFileSystem::get_path("/resource/shaders/square_matrix.frag");
	auto is_valid = !(vs_file.empty() || ps_file.empty());
	if (!is_valid) {
		BOOST_ASSERT_MSG(is_valid, "ERROR: Shader file load fail.");
		return;
	}
	shader = std::make_unique<VzShader>(vs_file.c_str(), ps_file.c_str());

	// initialize geometry
	auto vertices_size = vertices.size() * sizeof(float) * 3;
	auto indices_size = indices.size() * sizeof(unsigned) * 2;
	auto vertices_ptr = vertices.data();
	auto indices_ptr = indices.data();

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices_ptr, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, indices_ptr, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// init model matrix
	model_matrix = glm::translate(model_matrix, glm::vec3(0.0f));
}

void VzCubeEntity::render()
{
	view_matrix = VzCore::Camera.get_view_matrix();
	projection_matrix = VzCore::Camera.get_projection_matrix();

	shader->use();
	shader->set_mat4("model", model_matrix);
	shader->set_mat4("view", view_matrix);
	shader->set_mat4("projection", projection_matrix);

	GLint last_blend_src_alpha; glGetIntegerv(GL_BLEND_SRC_ALPHA, &last_blend_src_alpha);
	GLboolean last_enable_blend = glIsEnabled(GL_BLEND);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLineWidth((GLfloat)0.5f);

	glBindVertexArray(vao);

	auto indicesSize = indices.size() * sizeof(unsigned) * 2;
	glDrawElements(GL_LINES, indicesSize, GL_UNSIGNED_INT, 0);

	glLineWidth((GLfloat)1.0f);
	glBlendFunc(GL_SRC_ALPHA, last_blend_src_alpha);
	if (last_enable_blend) glEnable(GL_BLEND); else glDisable(GL_BLEND);
}

void VzCubeEntity::deinit()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
}

void VzCubeEntity::setup_cube(const VzCubeCreateInfo & info)
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
			indices.push_back(glm::uvec2(start_index, end_index));
		}

	////////////////////////////////////////////////////////////
	// axis-y line	
	for (int z = 0; z < info.dim_z + 1; ++z) 
		for (int x = 0; x < info.dim_x + 1; ++x) {
			int start_index = x + (z * (info.dim_x + 1));
			int end_index = x + (info.dim_y * (info.dim_x + 1) * (info.dim_z + 1));
			end_index += (z * (info.dim_x + 1));
			indices.push_back(glm::uvec2(start_index, end_index));
		}

	////////////////////////////////////////////////////////////
	// axis-z line	
	for (int y = 0; y < info.dim_y + 1; ++y) 
		for (int x = 0; x < info.dim_x + 1; ++x) {
			int start_index = x + (y * ((info.dim_x + 1) * (info.dim_z + 1)));
			int end_index = x + ((info.dim_x + 1) * info.dim_z);
			end_index += y * (info.dim_z + 1) * (info.dim_x + 1);
			indices.push_back(glm::uvec2(start_index, end_index));
		}
}
