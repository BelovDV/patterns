#include "../include/settings.h"

Settings::Settings(const std::string& file_name) :
	file_name(file_name)
{
	std::ifstream in(file_name);
	if (!in.is_open())
		return;

	in >> screen_size.x >> screen_size.y;

	for (int i = 0; i != Text::Type::overall_count; ++i)
	{
		int x;
		in >> x;
		Text::patterns[i]->set_size(x);
		std::string vsp;
		in >> vsp;
		Text::patterns[i]->set_font(vsp);
	}
}

Settings::~Settings()
{
	std::ofstream out(file_name);

	if (!out.is_open())
		Log::add("settings", "cann't find: " + file_name);

	out	<< screen_size.x << ' ' << screen_size.y << "\n\n";
	
	for (int i = 0; i != Text::Type::overall_count; ++i)
		out << Text::patterns[i]->get_size() << ' ' << Text::patterns[i]->get_font_file() << '\n';
}

void Settings::set_screen(int width, int height)
{
	screen_size.x = width;
	screen_size.y = height;
}

gi::Vector Settings::get_screen()
{
	return screen_size;
}

void Settings::set_text(Text::Type type, gi::Text& text)
{
	Text::patterns[type]->set_text(&text);
}

void Settings::set_font(Text::Type type, const std::string& file)
{
	Text::patterns[type]->set_font(file);
}

void Settings::set_text_size(Text::Type type, int size)
{
	Text::patterns[type]->set_size(size);
}