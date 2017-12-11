//---------------------------------------------------------
// Copyright (C) NSXTSoft. All rights reserved.

// ********************************************************
// File name : Camera.h
// Created   : 2017/08/09 by SungHoon Ko
// ********************************************************
//
///////////////////////////////////////////////////////////
#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include "core.h"

class VzCamera {
public:
	enum Camera_Movement { FORWARD, BACKWARD, LEFT, RIGHT };
	const float YAW = -90.0f;
	const float PITCH = 0.0f;
	const float SPEED = 2.5f;
	const float SENSITIVITY = 0.1f;
	const float ZOOM = 45.0f;

public:
	// Camera Attributes
	glm::vec3 Position;
	glm::vec3 Target;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;	
	glm::mat4 Projection;

	int ScreenWidth;
	int ScreenHeight;

	// Eular Angles
	float Yaw;
	float Pitch;

	// Camera options
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

public:
	VzCamera() :
		Position(glm::vec3(0.0f, 0.0f, 0.0f)),
		Target(glm::vec3(0.0f, 0.0f, -1.0f)),
		Up(glm::vec3(0.0f, 0.0f, 0.0f)),
		WorldUp(glm::vec3(0.0f, 1.0f, 0.0f)),
		ScreenWidth(0), ScreenHeight(0),
		Yaw(YAW), Pitch(PITCH),
		MovementSpeed(SPEED),
		MouseSensitivity(SENSITIVITY),
		Zoom(ZOOM) { }

	void initialize() {
		_update_camera_vector();
		_update_projection_matrix();
	}

	void get_screen_size(int& width, int& height) {
		width = ScreenWidth;
		height = ScreenHeight;
	}

	glm::mat4 get_view_matrix() {
		return glm::lookAt(Position, Position + Target, Up);
	}

	glm::mat4 get_projection_matrix() {
		return Projection;
	}

	void process_keyboard(Camera_Movement direction, float delta_time) {
		float velocity = MovementSpeed * delta_time;
		if (direction == FORWARD)
			Position += Target * velocity;
		if (direction == BACKWARD)
			Position -= Target * velocity;
		if (direction == LEFT)
			Position += Right * velocity;
		if (direction == RIGHT)
			Position -= Right * velocity;
	}

	void process_mouse_movement(float xoffset, float yoffset, bool constrain_pitch = true) {
		xoffset *= MouseSensitivity;
		yoffset *= MouseSensitivity;

		Yaw -= xoffset;
		Pitch += yoffset;

		// Make sure that when pitch is out of bounds, screen doesn't get flipped
		if (constrain_pitch) {
			if (Pitch > 89.0f)
				Pitch = 89.0f;
			if (Pitch < -89.0f)
				Pitch = -89.0f;
		}

		// Update Target(front), Right and Up Vectors using the updated Eular angles
		_update_camera_vector();
	}

	void process_mouse_scroll(float yoffset) {
		if (Zoom >= 1.0f && Zoom <= 45.0f)
			Zoom -= yoffset;

		if (Zoom <= 1.0f)
			Zoom = 1.0f;

		if (Zoom >= 45.0f)
			Zoom = 45.0f;

		_update_projection_matrix();
	}
	
private:
	// Calculates the target(front) vector from the Camera's (updated) Eular Angles
	void _update_camera_vector() {
		// Calculate the new Target(front) vector
		glm::vec3 target;
		target.x = cos(glm::radians(Pitch)) * cos(glm::radians(Yaw));
		target.y = sin(glm::radians(Pitch));
		target.z = cos(glm::radians(Pitch)) * sin(glm::radians(Yaw));

		Target = glm::normalize(target);

		// Also re-calculate the Right and Up vector
		// Normalize the vectors, because their length gets closer to 0
		// the more you look up or down which results in slower movement.
		Right = glm::normalize(glm::cross(Target, WorldUp));
		Up = glm::normalize(glm::cross(Right, Target));
	}

	// Calculate the Projection marix
	void _update_projection_matrix() {
		glfwGetWindowSize(VzGlobal::WindowCtx, &ScreenWidth, &ScreenHeight);
		Projection = glm::perspective(glm::radians(Zoom), (float)ScreenWidth / (float)ScreenHeight, 0.1f, 100.0f);
	}
};