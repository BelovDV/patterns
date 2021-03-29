#include <SFML/Graphics.hpp>

#include "../include/interactive_fiction.h"
#include "../include/start_menu.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1600, 900), "SFML works!", sf::Style::None);
	window.setPosition(sf::Vector2i(0, 0));

	window.display();

	Start_menu menu(window);
	menu.work();

	return 0;
}