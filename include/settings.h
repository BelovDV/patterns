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

	void set_text(Text::text_list_name name, const sf::Text& pattern);
	void set_font(Text::text_list_name name, const std::string& file_name);
	void set_text_size(Text::text_list_name name, int size);
private:
	int screen_width = 1920, screen_height = 1080;
	std::string file_name;
	std::vector<std::pair<Text::text_list_name, std::string>> fonts;
};