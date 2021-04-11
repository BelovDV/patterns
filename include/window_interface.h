#pragma once

class Window_interface
{
public:

public:
	Window_interface& operator*() { return *this; }
	const Window_interface& operator*() const { return *this; }
public:
	virtual void display() = 0;
	virtual bool is_open() = 0;
	virtual bool poll_event(gi::Event& event) = 0;
	virtual gi::Vector get_mouse_position() = 0;
	virtual void set_screen(gi::Rect rect) = 0;
	virtual gi::Vector get_screen_size() = 0;
};