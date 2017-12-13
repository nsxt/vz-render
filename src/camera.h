#pragma once

/*
Camera Module
referenced by https://github.com/hmazhar/moderngl_camera
*/

enum class VzCameraType { 
	ORTHO, FREE 
}
;
enum class VzCameraDirection {
	UP, DOWN, LEFT, RIGHT, FORWARD, BACK
};

class VzCamera {
public:
	VzCamera();
	virtual ~VzCamera();

	void update();

	void reset();
	
	void move();

	void change_pitch(float degrees);
	void change_heading(float degrees);

	void move_2d(int x, int y);

	void set_mode(VzCameraType mode);
	void set_position(glm::vec3 pos);
	void set_lookat(glm::vec3 pos);
	void set_fov(double fov);
	void set_viewport(int loc_x, int loc_y, int width, int height);
	void set_clipping(double near, double far);

	void get_viewport(int& loc_x, int& loc_y, int& width, int& height);
	void get_matricies(glm::mat4& P, glm::mat4& V);

protected:

private:
	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4 model;
	glm::mat4 MVP;

	glm::vec3 camera_position;
	glm::vec3 camera_position_delta;
	glm::vec3 camera_look_at;
	glm::vec3 camera_direction;
	glm::vec3 camera_up;

	VzCameraType camera_mode { VzCameraType::FREE };

	int viewport_x;
	int viewport_y;

	int window_width;
	int window_height;

	double aspect;
	double field_of_view;
	double near_clip;
	double far_clip;

	float camera_scale;
	float camera_heading;
	float cameara_pitch;

	float max_pitch_rate;
	float max_heading_rate;
};