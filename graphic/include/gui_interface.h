#pragma once

#include "gui_objects.h"

class Gui_interface
{
public:
	enum Condition
	{
		none,
		beginning,
		loading,
		game,
		exit
	};
	class Target_form
	{
	public:
		Target_form(std::vector<gi::Object*>& objects) : objects(objects) {}
	public:
		void add(gi::Object* object)
		{
			// Object* - form.add(0, 0, new Label(...));
			objects.push_back(object);
		}
	private:
		std::vector<gi::Object*>& objects;
	};
public:
	Gui_interface() {}
public:
	virtual void get_targets(Target_form& form) = 0;
	virtual void set_event(int id) = 0;
    virtual Condition get_condition() = 0;
};