#pragma once

#include "text.h"
#include "gui_interface.h"
#include "window_interface.h"
#include "gui_objects.h"
#include "log.h"
#include "settings.h"
#include "position.h"

class GUI
{
public:
	GUI(Gui_interface* worker, Window_interface* window, Settings* settings);
	~GUI();
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
	Window_interface* window;
	Settings* settings;
	Gui_interface* worker;
};