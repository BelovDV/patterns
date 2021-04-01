#pragma once

#include "text.h"
#include "log.h"

class Settings
{
public:
	Settings(const std::string& file_name);
	~Settings();
public:
	void set_screen(int width, int height);
	sf::Vector2u get_screen();

	void set_text(Text::Type type, const sf::Text& pattern);
	void set_font(Text::Type type, const std::string& file_name);
	void set_text_size(Text::Type type, int size);
private:
	sf::Vector2u screen_size;
	std::string file_name;
};