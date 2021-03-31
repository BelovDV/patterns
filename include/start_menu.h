#pragma once

#include "../include/interactive_fiction.h"
#include "../include/settings.h"

#include <SFML/Graphics.hpp>

class Start_menu
{
public:
	Start_menu(sf::RenderWindow& window);
public:
	// get result game?
	void work();
private:
	void set_coordinates();
	void draw();
	void refresh();
	void event_movemouse();
	void event_pressmouse();
	void event_presskey(sf::Keyboard::Key);
	void options_screen();
	void options_fonts();
private:
	Settings settings;
	sf::RenderWindow& window;
	sf::Texture t_background;
	sf::Sprite s_background;
	Interactive_fiction fiction;
	std::vector<sf::Rect<int>> buttons;
	std::vector<sf::Text> options;
	std::vector<sf::Text> messages;
	sf::Vector2i angle;
	int selected = -1;
};