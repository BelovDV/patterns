#include "../include/gui_objects.h"

Gui_objects::Object::Object(Position_type type, int number) :
	number_in_position(number),
	pos_type(type)
{}

Gui_objects::Label::Label(Position_type position, int number_in_position, sf::Text text) :
	Object(position, number_in_position),
	text(text),
	type(Back_type::none)
{
	area = text.getGlobalBounds();
}

Gui_objects::Label::Label(Position_type position, int number_in_position, sf::Text text, sf::FloatRect areaa, Back_type type) :
	Object(position, number_in_position),
	text(text),
	type(type)
{
	area = areaa;
}

void Gui_objects::Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (type != Back_type::none) {}
	target.draw(text, states);
}

void Gui_objects::Label::set_position(sf::Vector2f pos)
{
	position = pos;
	text.setPosition(pos);
	area = text.getGlobalBounds();
}

Gui_objects::Button::Button(Position_type position, int number, int id, sf::Text text) :
	Label(position, number, text),
	Executable(id)
{}

Gui_objects::Button::Button(Position_type position, int number, int id, sf::Text text, sf::FloatRect area, Back_type type) :
	Label(position, number, text, area, type),
	Executable(id)
{}

Gui_objects::List_objects::List_objects(Position_type position, int number, Object* head, std::vector<Object*>&& objects) :
	Object(position, number),
	head(head),
	objects(objects)
{}

void Gui_objects::List_objects::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*head, states);
	for (auto& it : objects)
		target.draw(*it, states);
}

void Gui_objects::List_objects::set_position(sf::Vector2f pos)
{
	head->set_position(pos);
	area = head->get_area();
	for (auto it : objects)
	{
		pos = sf::Vector2f(area.left, area.top + area.height);
		it->set_position(pos);
		area.height += it->get_area().height;
		area.width = std::max(area.width, it->get_area().width);
	}
}