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
	gi::Vector get_screen();

	void set_text(Text::Type type, gi::Text& pattern);
	void set_font(Text::Type type, const std::string& file_name);
	void set_text_size(Text::Type type, int size);
private:
	gi::Vector screen_size;
	std::string file_name;
};