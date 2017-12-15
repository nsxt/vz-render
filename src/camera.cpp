#include "core.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

void VzCamera::update()
{
	glViewport(viewport_x, viewport_y, window_width, window_height);

	camera_direction = glm::normalize(camera_look_at - camera_position);

	if (camera_type == VzCameraType::ORTHO) {
		projection = glm::ortho(-1.5f * float(aspect), 1.5f * float(aspect), -1.5f, 1.5f, -10.0f, 10.f);
	}
	else if (camera_type == VzCameraType::FREE) {
		projection = glm::perspective(field_of_view, aspect, near_clip, far_clip);

		// determine axis for pitch rotation & compute quaternion
		glm::vec3 prev_right = glm::cross(camera_direction, camera_up);
		glm::quat quat_pitch = glm::angleAxis(camera_pitch, prev_right);

		// determine heading quaternion
		glm::quat quat_heading = glm::angleAxis(camera_heading, camera_up);

		// combined two quaternion rotation using cross product.
		glm::quat quat_rotation = glm::cross(quat_pitch, quat_heading);
		quat_rotation = glm::normalize(quat_rotation);

		// update the direction from the quaternion & position & look at
		camera_direction = glm::rotate(quat_rotation, camera_direction);
		camera_right = glm::cross(camera_direction, camera_up);
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

void VzCamera::move(VzCameraDirection dir)
{
	float weight = camera_scale * VzCore::Timer.time_difference();

	if (camera_type == VzCameraType::FREE) {
		switch (dir) {
			case VzCameraDirection::UP:
				camera_position_delta += camera_up * weight;
				break;
			case VzCameraDirection::DOWN:
				camera_position_delta -= camera_up * weight;
				break;
			case VzCameraDirection::LEFT:
				camera_position_delta -= camera_right * weight;
				break;
			case VzCameraDirection::RIGHT:
				camera_position_delta += camera_right * weight;
				break;
			case VzCameraDirection::FORWARD:
				camera_position_delta += camera_direction * weight;
				break;
			case VzCameraDirection::BACKWARD:
				camera_position_delta -= camera_direction * weight;
				break;
		}
	}
}

void VzCamera::change_pitch(float degrees)
{
	camera_pitch += VzUtil::clamp(degrees, -max_pitch_rate, max_pitch_rate);
	camera_pitch -= VzUtil::clamp(camera_pitch, -360.0f, 360.0f);
}

void VzCamera::change_heading(float degrees)
{
	degrees = VzUtil::clamp(degrees, -max_heading_rate, max_heading_rate);

	// This controls how the heading is changed if the camera is pointed straight up or down
	if ((camera_pitch > 90.f && camera_pitch < 270.f) || (camera_pitch < -90.f && camera_pitch > -270.f))
		camera_heading -= degrees;
	else
		camera_heading += degrees;

	camera_heading -= VzUtil::clamp(camera_heading, -360.f, 360.f);
}

