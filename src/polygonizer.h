#pragma once


struct VzCell {
	glm::vec3 position;
	std::vector<glm::vec3> vertices;
	std::vector<unsigned> indicies;
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

	const unsigned get_case_code(const VzCornerValue& V);
	void polygonization(const VzCornerValue& V, VzCell& cell);

protected:

private:

};

