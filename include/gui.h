#pragma once

#include "text.h"
#include "gui_interface.h"
#include "gui_objects.h"
#include "log.h"

class GUI
{
public:
	GUI(Gui_interface* worker, Graphic_interface* window);
public:
	void work();
	void draw();
	void set_coordinates();
	void event_movemouse();
	void event_pressmouse(); // only one object
	void event_presskey(int key);
	void take_objects();
	void refresh();
private:
	std::vector<gi::Texture*> t_background;
	std::vector<gi::Sprite*> s_background;
	std::vector<gi::Object*> objects;
	std::vector<gi::Executable*> executable;
	std::vector<gi::Executable*> selected;
	Gui_interface* worker;
	Graphic_interface* window;
};