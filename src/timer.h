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
	VzTimer() :
		_is_one_frame{false}, _elapsed_time{0.0f}, _delta_time{0.0f}, _time_diff{0.0f},
		_target_fps{0.0f}, _current_fps{0.0f}, _alpha_time{0.0f}, _frame_count{1} {}

	~VzTimer() {}

	void pre_think() {};

	void think() {
		update();

		if (is_delta_arrival()) {
			_is_one_frame = true;
		}
	}

	void post_think() {
		if (_is_one_frame) {
			_is_one_frame = false;
			reset_delta();
			update_frame_count();
			calc_fps();
		}
	}

	void initialize() {
		_previous_time = clock::now();
	}	

	inline void update() {
		_current_time = clock::now();
		_time_diff = clamp<float>((float)(duration(_current_time - _previous_time).count() / 1000.f), 0.f, 1.f);
		_elapsed_time += _time_diff;
		_previous_time = _current_time;
		_delta_time += _time_diff;
		_alpha_time += _time_diff;
	}

	inline void calc_fps(float interval = 1.0f) {
		if (_alpha_time > interval) {
			_current_fps = (float)_frame_count / _alpha_time;
			_frame_count = 0;
			_alpha_time = 0.0f;
		}
	}

	inline bool is_delta_arrival() const {
		return (_delta_time >= 1.0f / _target_fps);
	}

	inline void reset_delta() {
		_delta_time = 0.0f;
	}

	inline void set_fps(float fps) {
		_target_fps = fps;
	}

	inline void update_frame_count() {
		_frame_count++;
	}

	inline float current_fps() const {
		return _current_fps;
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

	inline bool one_frame() const {
		return _is_one_frame;
	}

private:
	clock::time_point _current_time;
	clock::time_point _previous_time;

	bool _is_one_frame;
	float _elapsed_time;
	float _delta_time;	
	float _time_diff;
	float _target_fps;
	float _current_fps;
	float _alpha_time;
	int _frame_count;
};
