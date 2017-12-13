#include "core.h"

VzCamera::VzCamera()
{
	// todo : CppCoreGuidlines C.48
	camera_mode = VzCameraType::FREE;
	camera_up = glm::vec3(0.0f, 0.0f, 1.0f);
	field_of_view = 45.0;
}
