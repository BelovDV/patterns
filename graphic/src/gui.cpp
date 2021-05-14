#include "gui.h"

using namespace gi;

GUI::GUI(Gui_interface* worker, Window_interface* window, Settings* settings) :
	window(window),
	settings(settings),
	worker(worker)
{
	t_background.push_back(Texture::generate());
	if (!t_background[0]->load("../data/image/castle_1920_1080_my.jpeg"))
		Log::add("gui", "cannot load image: ");
	s_background.push_back(Sprite::generate());
	s_background[0]->set_texture(*t_background[0]);
	s_background[0]->set_scale((double)settings->get_screen().x / 1920, (double)settings->get_screen().y / 1080);
	window->set_screen(gi::Rect(0, 0, settings->get_screen().x, settings->get_screen().y));
}

GUI::~GUI()
{
	for (auto it : objects)
		delete it;
}

void GUI::work()
{
	refresh();
	take_objects();
	set_coordinates();
	draw();

	while (window->is_open())
	{
		gi::Event event;
		while (window->poll_event(event))
		{
			if (event.type == gi::Event_type::mouse_moved)
				event_movemouse();
			else if (event.type == gi::Event_type::mouse_button_pressed)
				event_pressmouse();
			else if (event.type == gi::Event_type::key_pressed)
				event_presskey(event.keycode);

			draw();
		}

		if (worker->get_condition() == Gui_interface::exit)
			break;
	}
}

void GUI::draw()
{
	s_background[0]->draw(*window);

	for (auto it : objects)
		it->draw(window);

	window->display();
}

void GUI::set_coordinates()
{
	if (window->get_screen_size() != settings->get_screen())
	{
		s_background[0]->set_scale((double)settings->get_screen().x / 1920, (double)settings->get_screen().y / 1080);
		window->set_screen(gi::Rect(0, 0, settings->get_screen().x, settings->get_screen().y));
	}
	std::vector<gi::Vector> pos(Position_type::count_of_types);

	if (settings->get_screen() != gi::Vector(1200, 800))
	{
		pos[left_up] = { 30, 30 };
		pos[left_down] = { 30, 1050 };
		pos[right_up] = { 1890, 30 };
		pos[right_down] = { 1890, 1050 };
		pos[exact_centre] = { 960, 540 };
		pos[shifting_space] = { 1200, 500 };
	}
	else
	{
		pos[left_up] = { 30, 30 };
		pos[left_down] = { 30, 1050 };
		pos[right_up] = { 1890, 30 };
		pos[right_down] = { 1890, 1050 };
		pos[exact_centre] = { 960, 540 };
		pos[shifting_space] = { 800, 400 };
	}

	for (auto it : objects)
	{
		auto& position = pos[it->get_pos_type()];

		it->set_position(position);

		position.y = it->get_area().height + it->get_area().top;
	}

	// TODO return to angle/centre
}

void GUI::event_movemouse()
{
	for (auto it : selected)
		it->select_off();
	selected.clear();
	auto coord = window->get_mouse_position();
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
	auto coord = window->get_mouse_position();
	for (auto it : executable)
		if (dynamic_cast<Object*>(it)->contain(coord))
		{
			worker->set_event(it->get_id());
			break;
		}
	take_objects();
	set_coordinates();
}

void GUI::event_presskey(int key)
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