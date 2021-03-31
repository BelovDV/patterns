#include "../include/settings.h"

Settings::Settings(const std::string& file_name) :
	file_name(file_name)
{
	std::ifstream in(file_name);
	if (!in.is_open())
		return;

	int counter;

	in >> screen_width >> screen_height;

	in >> counter;
	fonts.resize(counter);
	for (int i = 0; i != counter; ++i)
	{
		int val;
		in >> val >> fonts[i].second;
		fonts[i].first = Text::text_list_name(val);
	}
}

Settings::~Settings()
{
	std::ofstream out(file_name);

	out	<< screen_width << ' ' << screen_height << '\n';
	
	out << fonts.size() << '\n';
	for (auto& it : fonts)
		out << it.first << ' ' << it.second << '\n';
}

void Settings::set_screen(int width, int height)
{
	screen_width = width;
	screen_height = height;
}

sf::Vector2u Settings::get_screen()
{
	return sf::Vector2u(screen_width, screen_height);
}

void Settings::set_text(Text::text_list_name name, const sf::Text& text)
{
	Text::text_list[name]->set_text(text);
}

void Settings::set_font(Text::text_list_name name, const std::string& file)
{
	Text::text_list[name]->set_font(file);
}

void Settings::set_text_size(Text::text_list_name name, int size)
{
	Text::text_list[name]->set_size(size);
}