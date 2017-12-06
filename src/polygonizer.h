#pragma once


struct VzCell {
	glm::vec3 position;
	std::vector<glm::vec3> vertices;
	std::vector<unsigned> indices;
};

struct VzCornerValue {
	std::array<char, 8> D;
	std::array<glm::vec3, 8> P;
	
	VzCornerValue() 
		: D{{}}, P{{}}
	{}
};

class VzPolygonizer {
public:
	VzPolygonizer() = default;			// default ctor
	virtual ~VzPolygonizer() = default;	// default dtor		

	// copy ctor & assign
	// move ctor & assign

	// for test
	void init();
	void render();
	void deinit();

	void setup_cell();

	const unsigned get_case_code(const VzCornerValue& V);
	void polygonization(const VzCornerValue& V, VzCell& cell);

protected:

private:
	VzCell cell_1;
	VzCornerValue corner_value_1;
	
	std::unique_ptr<VzShader> shader;
	GLuint vbo;
	GLuint ebo;
	GLuint vao;

	glm::mat4 model_mat;
	glm::mat4 view_mat;
	glm::mat4 projection_mat;
};

