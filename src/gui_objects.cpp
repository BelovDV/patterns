#include "../include/gui_objects.h"

gi::Object::Object(Position_type type) :
	pos_type(type)
{}

gi::Label::Label(Position_type position, gi::Text* text) :
	Object(position),
	text(text)
{
	area = text->get_bounds();
}

void gi::Label::draw(Window_interface& target) const
{
	text->draw(target);
}

void gi::Label::set_position(gi::Vector pos)
{
	position = pos;
	text->set_position(pos);
	area = text->get_bounds(); // this was the reason of hard mistake...
	/*area.left = pos.x;
	area.top = pos.y;*/
}

gi::Button::Button(Position_type position, int id, gi::Text* text) :
	Label(position, text),
	Executable(id)
{}

gi::Button::Button(Position_type position, int id, gi::Text* text, gi::Rect areaa) :
	Label(position, text),
	Executable(id)
{
	area = areaa;
}

void gi::Button::select_on()
{
	this->text->set_color(gi::Color(0, 255, 0));
}

void gi::Button::select_off()
{
	this->text->set_color(gi::Color(0, 0, 0));
}

gi::List_objects::List_objects(Position_type position, std::vector<Object*>&& objects) :
	Object(position),
	objects(objects)
{}

void gi::List_objects::draw(Window_interface& window) const
{
	for (auto& it : objects)
		it->draw(window);
}