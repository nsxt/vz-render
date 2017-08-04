#include "core.h"

VzCamera VzCore::Camera;
VzPlane VzCore::Plane(glm::vec3(0.0f, 0.0f, 0.0f));
VzCube VzCore::Cube(glm::vec3(0.0f, 0.0f, 0.0f));

float VzCore::DeltaTime = 0.0f;
float VzCore::LastFrame = 0.0f;