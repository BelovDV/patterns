#pragma once

#include <SFML/Graphics.hpp>

#include "text.h"
#include "gui_interface.h"
#include "gui_objects.h"
#include "log.h"

class GUI
{
public:
	GUI(Gui_interface* worker);
public:
	void work();
	void draw();
	void set_coordinates();
	void event_movemouse();
	void event_pressmouse(); // only one object
	void event_presskey(sf::Keyboard::Key key);
	void take_objects();
	void refresh();
private:
	std::vector<sf::Texture*> t_background;
	std::vector<sf::Sprite> s_background;
	std::vector<Gui_objects::Object*> objects;
	std::vector<Gui_objects::Executable*> executable;
	std::vector<Gui_objects::Executable*> selected;
	Gui_interface* worker;
	sf::RenderWindow window;
};