#include "../include/start_menu.h"

Start_menu::Start_menu(sf::RenderWindow& window) :
	window(window),
	fiction("../data/cond.txt")
{
	font.loadFromFile("../data/font.ttf");
	t_background.loadFromFile("../data/image/screen.jpg");
	s_background.setTexture(t_background);

	last_selected_button = 0;
	leftup_angle = sf::Vector2i(1000, 500);
	font_size_message = 35;
	font_size_other = 30;
	string_length = 100;
}

void Start_menu::event_movemouse()
{
	auto coord = sf::Vector2i(window.mapPixelToCoords(sf::Mouse::getPosition()));
	for (int i = 0; i != buttom_coordinates.size(); ++i)
		if (buttom_coordinates[i].contains(coord))
		{
			if (last_selected_button != -1)
				options[last_selected_button].setColor(sf::Color::White);
			last_selected_button = i;
			options[i].setColor(sf::Color::Green);
			return;
		}
}

void Start_menu::event_pressmouse()
{
	auto coord = sf::Vector2i(window.mapPixelToCoords(sf::Mouse::getPosition()));
	for (int i = 0; i != buttom_coordinates.size(); ++i)
		if (buttom_coordinates[i].contains(coord))
		{
			fiction.press(i);
			set_coordinates();
			return;
		}
}

void Start_menu::event_presskey(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::Enter && last_selected_button != -1)
		fiction.press(last_selected_button), set_coordinates();
	if (key == sf::Keyboard::Up)
		if (last_selected_button != 0 && last_selected_button != -1)
		{
			options[last_selected_button].setColor(sf::Color::White);
			--last_selected_button;
			options[last_selected_button].setColor(sf::Color::Green);
		}
		else
		{
			if (last_selected_button != -1)
				options[last_selected_button].setColor(sf::Color::White);
			last_selected_button = fiction.get().ways.size() - 1;
			options[last_selected_button].setColor(sf::Color::Green);
		}
	if (key == sf::Keyboard::Down && last_selected_button != fiction.get().ways.size() - 1)
	{
		if (last_selected_button != -1)
			options[last_selected_button].setColor(sf::Color::White);
		++last_selected_button;
		options[last_selected_button].setColor(sf::Color::Green);
	}
}

void Start_menu::options_screen() // TODO - safe settings
{
	if (fiction.get_last_target() == "1600:900")
		window.setSize(sf::Vector2u(1600, 900));
	if (fiction.get_last_target() == "1500:800")
		window.setSize(sf::Vector2u(1500, 800));
	if (fiction.get_last_target() == "1920:1080")
		window.setSize(sf::Vector2u(1920, 1080)); // TODO - image
}

void Start_menu::work()
{
	set_coordinates();
	draw();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::EventType::MouseMoved)
				event_movemouse();
			if (event.type == sf::Event::EventType::MouseButtonPressed &&
				event.mouseButton.button == sf::Mouse::Left)
				event_pressmouse();
			if (event.type == sf::Event::EventType::KeyPressed)
				event_presskey(event.key.code);

			if (fiction.get_last_condition() == "screen")
				options_screen();
			if (fiction.get_condition() == "exit")
				return;

			draw();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			break; // debug
	}
}

void Start_menu::set_coordinates()
{
	last_selected_button = -1;

	options.clear();
	buttom_coordinates.clear();

	auto& condition = fiction.get();

	sf::Text mes(condition.message, font, font_size_message);
	mes.move(leftup_angle.x, leftup_angle.y); // TODO
	message = mes;

	for (int i = 0; i != condition.ways.size(); ++i)
	{
		sf::Text text(condition.ways[i].name, font, font_size_other);
		text.move(
			leftup_angle.x, 
			(font_size_message + 10) * fiction.get_message_size() + leftup_angle.y + i * font_size_other);
		options.push_back(text);

		buttom_coordinates.push_back(sf::Rect<int>(
			leftup_angle.x, 
			(font_size_message + 10) * fiction.get_message_size() + leftup_angle.y + i * font_size_other,
			string_length,
			font_size_other + 5));
	}
}

void Start_menu::draw()
{
	window.draw(s_background);
	window.draw(message);
	for (const auto& iter : options)
		window.draw(iter);

	window.display();
}