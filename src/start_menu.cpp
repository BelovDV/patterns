#include "../include/start_menu.h"

Start_menu::Start_menu(sf::RenderWindow& window) :
	window(window),
	fiction("../data/cond.txt"),
	settings("../data/settings.txt")
{
	t_background.loadFromFile("../data/image/castle_1920_1080_my.jpg");
	s_background.setTexture(t_background);

	angle = sf::Vector2i(1200, 500);
}

void Start_menu::refresh()
{
	
}

void Start_menu::event_movemouse()
{
	auto coord = sf::Mouse::getPosition();
	for (int i = 0; i != buttons.size(); ++i)
		if (buttons[i].contains(coord))
		{
			if (selected != -1)
				options[selected].setColor(sf::Color::Black);
			selected = i;
			options[i].setColor(sf::Color::Green);
			return;
		}
	if (selected != -1)
	{
		options[selected].setColor(sf::Color::Black);
		selected = -1;
	}
}

void Start_menu::event_pressmouse()
{
	auto coord = sf::Mouse::getPosition();
	for (int i = 0; i != buttons.size(); ++i)
		if (buttons[i].contains(coord))
		{
			fiction.press(i);
			set_coordinates();
			return;
		}
}

void Start_menu::event_presskey(sf::Keyboard::Key key)
{
	if (selected != -1)
		options[selected].setColor(sf::Color::Black);

	if (key == sf::Keyboard::Enter && selected != -1)
	{
		fiction.press(selected);
		set_coordinates();
	}
	else if (key == sf::Keyboard::Up)
	{
		if (selected == -1 || selected == 0)
			selected = options.size() - 1;
		else
			--selected;
	}
	else if (key == sf::Keyboard::Down)
	{
		if (selected == options.size() - 1)
			selected = 0;
		else
			++selected;
	}

	if (selected != -1)
		options[selected].setColor(sf::Color::Green);
}

void Start_menu::options_screen()
{
	
}

void Start_menu::options_fonts()
{
	Text::text_list_name name;
	auto& vsp = fiction.get_last_condition();
	if (*vsp[0] == "title")
		name = Text::text_list_name::e_title;
	else if (*vsp[0] == "text")
		name = Text::text_list_name::e_text;
	else if (*vsp[0] == "offer")
		name = Text::text_list_name::e_offer;
	else
		return;

	if (*vsp[1] == "10")
		settings.set_text_size(name, 10);
	if (*vsp[1] == "15")
		settings.set_text_size(name, 15);
	if (*vsp[1] == "20")
		settings.set_text_size(name, 20);
	if (*vsp[1] == "25")
		settings.set_text_size(name, 25);
	if (*vsp[1] == "30")
		settings.set_text_size(name, 30);

	if (*vsp[2] == "first")
		settings.set_font(name, "../data/font.ttf");
	if (*vsp[2] == "second")
		settings.set_font(name, "../data/second.ttf");

	fiction.forget();

	set_coordinates();
}

void Start_menu::work()
{
	refresh();
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

			if (fiction.get_last_target_name() == "apply")
			{
				if (fiction.get_position() == "screen")
					options_screen();
				else if (fiction.get_position() == "fonts")
					options_fonts();
			}
			
			if (fiction.get_position() == "exit")
				return;

			draw();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			break; // debug
	}
}

void Start_menu::set_coordinates()
{
	selected = -1;

	options.clear();
	buttons.clear();
	messages.clear();

	auto& info = fiction.get();
	auto& ways = fiction.get().ways;

	messages.push_back(Text::text.generate(info.message, angle));
	int offer_heigh = Text::offer.get_size() + 5;
	sf::Vector2i position(angle + sf::Vector2i(10, 5 + Text::text.get_size() * Text::text.get_number_line(info.message)));
	for (int i = 0; i != ways.size(); ++i, position.y +=offer_heigh)
	{
		options.push_back(Text::offer.generate(ways[i].name, position));
		buttons.push_back(sf::Rect<int>(options.back().getGlobalBounds()));
	}

	int drop = fiction.get_chosen_list();
	auto& condition = fiction.get_condition();
	for (int i = 0; i != info.lists.size(); ++i, position.y += offer_heigh)
	{
		options.push_back(Text::offer.generate(*condition[i], position));
		buttons.push_back(sf::Rect<int>(options.back().getGlobalBounds()));
		if (i == drop)
			for (int j = 0; j != info.lists[drop].values.size(); ++j)
			{
				position.y += offer_heigh - 5;
				options.push_back(Text::offer.generate(info.lists[drop].values[j], position + sf::Vector2i(5, 0)));
				buttons.push_back(sf::Rect<int>(options.back().getGlobalBounds()));
			}
	}
}

void Start_menu::draw()
{
	window.draw(s_background);

	for (const auto& iter : options)
		window.draw(iter);
	for (const auto& iter : messages)
		window.draw(iter);
	for (const auto& iter : buttons) // debug
	{
		sf::RectangleShape rect(sf::Vector2f(iter.width, iter.height));
		rect.move(iter.left, iter.top);
		rect.setOutlineColor(sf::Color::White);
		rect.setOutlineThickness(1);
		rect.setFillColor(sf::Color::Transparent);
		window.draw(rect);
	}

	window.display();
}