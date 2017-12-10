#pragma once

struct VzCubeCreateInfo {
	glm::vec3 start_pos;
	int dim_x, dim_y, dim_z;
	float len_weight;
};

class VzCubeRenderer {
public:
	// ctor & dtor
	VzCubeRenderer() = default;
	virtual ~VzCubeRenderer() = default;

	// move ctor & assign
	VzCubeRenderer(VzCubeRenderer&&) = default;
	VzCubeRenderer& operator=(VzCubeRenderer&&) = default;

	// copy ctor & assign
	VzCubeRenderer(const VzCubeRenderer&) = default;
	VzCubeRenderer& operator=(const VzCubeRenderer&) = default;

	void init();
	void render();
	void deinit();

	void setup_cube(const VzCubeCreateInfo& info);

protected: // unchecked function for use by derived class implementations


private: // implementation details
	GLuint vao;
	GLuint vbo;
	GLuint ebo;
	
	std::unique_ptr<VzShader> shader;
	std::vector<glm::vec3> vertices;
	std::vector<glm::uvec2> indices;

	VzCubeCreateInfo created_info;
};