//---------------------------------------------------------
// Copyright (C) NSXTSoft. All rights reserved.

// ********************************************************
// File name : ui.h
// Created   : 2017/09/29 by SungHoon Ko
// ********************************************************
//
///////////////////////////////////////////////////////////
#pragma once

class VzUI {
public:
	VzUI();
	~VzUI();

public:
	void pre_think() {}
	void think();
	void post_think() {}


protected:
	void show_fixed_overay();
	void show_debug_property();

private:
	bool _is_show_fixed_overay;
	bool _is_show_debug_property;
};
