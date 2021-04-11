#pragma once

#include "graphic_interface.h"

#include <vector>

namespace gi
{
	enum Position_type
	{
		left_up,
		left_down,
		right_up,
		right_down,
		exact_centre,
		shifting_space,
		count_of_types
	};
	class Object : public gi::Drawable
	{
	public:
		Object(Position_type type);
		virtual ~Object() {}
	public:
		virtual void draw(Window_interface& window) const = 0;
		virtual void draw(Window_interface* window) const
		{
			this->draw(*window);
		}
		virtual gi::Rect get_area() const { return area; }
		virtual void set_position(gi::Vector pos) = 0;
		virtual bool contain(gi::Vector pos) const { return area.contain(pos); }
		Position_type get_pos_type() { return pos_type; }
		Object& operator*() { return *this; }
		const Object& operator*() const { return *this; }
	protected:
		Position_type pos_type;
		gi::Vector position;
		gi::Rect area;
	};
	class Executable
	{
	public:
		Executable(int id) : id(id) {}
	public:
		int get_id() { return id; }
		virtual void select_on() = 0;
		virtual void select_off() = 0;
	private:
		int id;
	};
	class Label : public Object
	{
	public:
		Label(Position_type position) : Object(position) {}
	public:
		virtual void draw(Window_interface& window) const = 0;
		virtual const gi::Text& get_text() const = 0;
		virtual void set_position(Vector position) = 0;
	};
	class Button : public Label, public Executable
	{
	public:
		Button(Position_type position, int id) : Label(position), Executable(id) {}
	public:
		virtual void select_on() = 0;
		virtual void select_off() = 0;
	};
	class Input : public Object {};
	class List_objects : public Object
	{
	public:
		List_objects(Position_type position) : Object(position) {}
	public:
		virtual void draw(Window_interface& window) const = 0;
		//virtual void set_position(gi::Vector pos) = 0;
	};
}