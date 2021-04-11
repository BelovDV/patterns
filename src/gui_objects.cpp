#include "../include/gui_objects_concrete.h"
#include "../include/log.h"

gi::Object::Object(Position_type type) :
	pos_type(type)
{}

gi_c::basic::Label::Label(gi::Position_type position, gi::Text* text) :
	gi::Label(position),
	text(text)
{
	area = text->get_bounds();
}

void gi_c::basic::Label::draw(Window_interface& target) const
{
	text->draw(target);
}

void gi_c::basic::Label::set_position(gi::Vector pos)
{
	position = pos;
	text->set_position(pos);
	area = text->get_bounds(); // this was the reason of hard mistake...
	/*area.left = pos.x;
	area.top = pos.y;*/
}

gi_c::basic::Button::Button(gi::Position_type position, int id, gi::Text* text) :
	gi::Button(position, id),
	text(text)
{
	area = text->get_bounds();
}

gi_c::basic::Button::Button(gi::Position_type position, int id, gi::Text* text, gi::Rect areaa) :
	gi::Button(position, id),
	text(text)
{
	area = areaa;
}

void gi_c::basic::Button::select_on()
{
	this->text->set_color(gi::Color(0, 255, 0));
}

void gi_c::basic::Button::select_off()
{
	this->text->set_color(gi::Color(0, 0, 0));
}

void gi_c::basic::Button::draw(Window_interface& target) const
{
	text->draw(target);
}

void gi_c::basic::Button::set_position(gi::Vector pos)
{
	position = pos;
	text->set_position(pos);
	area = text->get_bounds(); // this was the reason of hard mistake...
	/*area.left = pos.x;
	area.top = pos.y;*/
}

gi_c::basic::List_objects::List_objects(gi::Position_type position, std::vector<Object*>&& objects) :
	gi::List_objects(position),
	objects(objects)
{}

void gi_c::basic::List_objects::draw(Window_interface& window) const
{
	for (auto& it : objects)
		it->draw(window);
}

void gi_c::basic::List_objects::set_position(gi::Vector pos)
{

}