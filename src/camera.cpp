#include "core.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

void VzCamera::update()
{
	glViewport(viewport_x, viewport_y, window_width, window_height);

	camera_direction = glm::normalize(camera_look_at - camera_position);

	if (camera_mode == VzCameraType::ORTHO) {
		projection = glm::ortho(-1.5f * float(aspect), 1.5f * float(aspect), -1.5f, 1.5f, -10.0f, 10.f);
	}
	else if (camera_mode == VzCameraType::FREE) {
		projection = glm::perspective(field_of_view, aspect, near_clip, far_clip);

		// determine axis for pitch rotation & compute quaternion
		glm::vec3 right = glm::cross(camera_direction, camera_up);
		glm::quat quat_pitch = glm::angleAxis(camera_pitch, right);

		// determine heading quaternion
		glm::quat quat_heading = glm::angleAxis(camera_heading, camera_up);

		// combined two quaternion rotation using cross product.
		glm::quat quat_rotation = glm::cross(quat_pitch, quat_heading);
		quat_rotation = glm::normalize(quat_rotation);

		// update the direction from the quaternion & position & look at
		camera_direction = glm::rotate(quat_rotation, camera_direction);
		camera_position += camera_position_delta;
		camera_look_at = camera_position + camera_direction * 1.0f;

		// damping for smooth camera
		camera_heading *= 0.5f;
		camera_pitch *= 0.5f;
		camera_position_delta = camera_position_delta * 0.8f;
	}

	// compute the MVP
	view = glm::lookAt(camera_position, camera_look_at, camera_up);
	model = glm::mat4(1.0f);
	MVP = projection * view * model;
}
