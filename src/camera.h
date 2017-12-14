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
	VzCamera() = default;
	virtual ~VzCamera() = default;

	void update();
		
	void move(VzCameraDirection dir);
	void move_2d(int x, int y);

	void change_pitch(float degrees);
	void change_heading(float degrees);
	
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
	glm::mat4 projection {1.0f};
	glm::mat4 view {1.0f};
	glm::mat4 model {1.0f};
	glm::mat4 MVP {1.0f};

	glm::vec3 camera_position {0.0f};
	glm::vec3 camera_position_delta {0.0f};
	glm::vec3 camera_look_at {0.0f};
	glm::vec3 camera_direction {0.0f};
	glm::vec3 camera_up {0.0f, 0.0f, 1.0f};

	VzCameraType camera_mode { VzCameraType::FREE };

	int viewport_x {0};
	int viewport_y {0};

	int window_width {1280};
	int window_height {720};

	float aspect {0.0f};
	float field_of_view {45.0f};
	float near_clip {0.1f};
	float far_clip {100.0f};

	float camera_scale {0.5f};
	float camera_heading {0.0f};
	float camera_pitch {0.0f};

	float max_pitch_rate {5.0f};
	float max_heading_rate {5.0f};
};