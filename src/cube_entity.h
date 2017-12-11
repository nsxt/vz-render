#pragma once

struct VzCubeCreateInfo {
	glm::vec3 start_pos;
	int dim_x, dim_y, dim_z;
	float len_weight;
};

class VzCubeEntity {
public:
	// ctor & dtor
	VzCubeEntity() = default;
	virtual ~VzCubeEntity() = default;

	// move ctor & assign
	VzCubeEntity(VzCubeEntity&&) = default;
	VzCubeEntity& operator=(VzCubeEntity&&) = default;

	// copy ctor & assign
	VzCubeEntity(const VzCubeEntity&) = default;
	VzCubeEntity& operator=(const VzCubeEntity&) = default;

	void init();
	void render();
	void deinit();

	void setup_cube(const VzCubeCreateInfo& info);

protected: // unchecked function for use by derived class implementations


private: // implementation details
	glm::mat4 model_matrix;
	glm::mat4 view_matrix;
	glm::mat4 projection_matrix;

	GLuint vao;
	GLuint vbo;
	GLuint ebo;
	
	std::unique_ptr<VzShader> shader;
	std::vector<glm::vec3> vertices;
	std::vector<glm::uvec2> indices;

	VzCubeCreateInfo created_info;
};