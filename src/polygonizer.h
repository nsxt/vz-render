#pragma once

struct VzCornerValue {
	std::array<char, 8> D;
	
	VzCornerValue() 
		: D{{}} 
	{}
};

class VzPolygonizer {
public:
	VzPolygonizer() = default;			// default ctor
	virtual ~VzPolygonizer() = default;	// default dtor		

	// copy ctor & assign
	// move ctor & assign

	const unsigned get_case_code(const VzCornerValue& V);
	void polygonization(const VzCornerValue& V);

protected:

private:

};

