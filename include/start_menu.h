#include "../include/interactive_fiction.h"

#include <SFML/Graphics.hpp>

class Start_menu
{
public:
	Start_menu(sf::RenderWindow& window);
public:
	void event_movemouse();
	void event_pressmouse();
	void event_presskey(sf::Keyboard::Key);
	void options_screen();
	// get result game?
	void work();
private:
	void set_coordinates();
	void draw();
private:
	sf::RenderWindow& window;
	Interactive_fiction fiction;
	std::vector<sf::Rect<int>> buttom_coordinates;
	sf::Text message;
	std::vector<sf::Text> options;
	sf::Font font;
	sf::Texture t_background;
	sf::Sprite s_background;
	int last_selected_button;
	sf::Vector2i leftup_angle;
	int font_size_message;
	int font_size_other;
	int string_length = 100;
};