#include "../include/gui.h"

using namespace Gui_objects;

GUI::GUI(Gui_interface* worker) :
	worker(worker),
	window(sf::VideoMode(1820, 1080), "", sf::Style::None)
{
	t_background.push_back(new sf::Texture);
	if (!t_background[0]->loadFromFile("../data/image/castle_1920_1080_my.jpeg"))
		Log::add("gui", "cannot load image: ");
	s_background.push_back(sf::Sprite(*t_background[0]));

	window.setPosition(sf::Vector2i(0, 0));
}

void GUI::work()
{
	refresh();
	take_objects();
	set_coordinates();
	draw();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::EventType::MouseMoved)
				event_movemouse();
			else if (event.type == sf::Event::EventType::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
				event_pressmouse();
			else if (event.type == sf::Event::EventType::KeyPressed)
				event_presskey(event.key.code);

			draw();
		}

		if (worker->get_condition() == Gui_interface::Condition::exit)
			break;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			break; // debug
	}
}

void GUI::draw()
{
	window.draw(s_background[0]);

	for (auto it : objects)
	{
		window.draw(*it);
		// TODO - change position according text_type (for example - tab for offer_small)

		sf::RectangleShape rect({ it->get_area().width, it->get_area().height });
		rect.move(it->get_area().left, it->get_area().top);
		rect.setFillColor(sf::Color::Transparent);
		rect.setOutlineColor(sf::Color::White);
		rect.setOutlineThickness(1);
		window.draw(rect);
	}

	window.display();
}

void GUI::set_coordinates()
{
	std::vector<sf::Vector2f> pos(Position_type::count_of_types);
	pos[left_up] = { 30, 30 };
	pos[left_down] = { 30, 1050 };
	pos[right_up] = { 1890, 30 };
	pos[right_down] = { 1890, 1050 };
	pos[exact_centre] = { 960, 540 };
	pos[shifting_space] = { 1200, 500 };

	for (auto it : objects)
	{
		it->set_position(pos[it->get_pos_type()]);

		pos[it->get_pos_type()].y = it->get_area().height + it->get_area().top;
	}

	// TODO return to angle/centre
}

void GUI::event_movemouse()
{
	for (auto it : selected)
		it->select_off();
	selected.clear();
	auto coord = sf::Mouse::getPosition();
	for (auto it : executable)
	{
		auto iter = dynamic_cast<Object*>(it);
		if (iter && iter->contain(coord))
			selected.push_back(it);
	}
	for (auto it : selected)
		it->select_on();
}

void GUI::event_pressmouse()
{
	auto coord = sf::Mouse::getPosition();
	for (auto it : executable)
		if (dynamic_cast<Object*>(it)->contain(coord))
		{
			worker->set_event(it->get_id());
			break;
		}
	take_objects();
	set_coordinates();
}

void GUI::event_presskey(sf::Keyboard::Key key)
{

}

void GUI::take_objects()
{
	selected.clear();
	executable.clear();
	for (auto it : objects)
		delete it;
	objects.clear();

	Gui_interface::Target_form form(objects);
	worker->get_targets(form);

	std::sort(objects.begin(), objects.end(), [](Object* a, Object* b) {return a->get_number() < b->get_number(); });

	for (auto it : objects)
	{
		auto iter = dynamic_cast<Executable*>(it);
		if (iter)
			executable.push_back(iter);
	}
}

void GUI::refresh()
{

}