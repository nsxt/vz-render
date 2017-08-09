//---------------------------------------------------------
// Copyright (C) NSXTSoft. All rights reserved.

// ********************************************************
// File name : Timer.h
// Created   : 2017/08/09 by SungHoon Ko
// ********************************************************
//
///////////////////////////////////////////////////////////
#pragma once

class VzTimer {
	using clock = std::chrono::high_resolution_clock;
	using duration = std::chrono::duration<float, std::milli>;	

	template<typename T>
	T clamp(const T& n, const T& lower, const T& upper) {
		return std::max(lower, std::min(n, upper));
	}

public:
	VzTimer() : _delta_time{ 0.0f }, _elapsed_time { 0.f }, _time_diff{ 0.f }, _fps{ 0.f }, _frame_count{ 1 } {}
	~VzTimer() {}

	void initialize() {
		_previous_time = clock::now();
	}

	inline void update(float interval = 1.0f) {
		_current_time = clock::now();
		_time_diff = clamp<float>((float)(duration(_current_time - _previous_time).count() / 1000.f), 0.f, 1.f);
		_elapsed_time += _time_diff;
		_delta_time += _time_diff;
		_previous_time = _current_time;

		if (_delta_time > interval) {
			_fps = (float)_frame_count / _delta_time;
			_frame_count = 0;
			_delta_time = 0.0f;
		}
	}

	inline void update_frame_count() {
		_frame_count++;
	}

	inline float fps() const {
		return _fps;
	}

	inline float current_time() const {	
		duration epochTime = _current_time.time_since_epoch();
		return epochTime.count();
	}

	inline float elapsed_time() const {
		return _elapsed_time;
	}

	inline float time_difference() const {
		return _time_diff;
	}

private:
	clock::time_point _current_time;
	clock::time_point _previous_time;

	float _elapsed_time;
	float _delta_time;
	float _time_diff;
	float _fps;
	int _frame_count;
};
