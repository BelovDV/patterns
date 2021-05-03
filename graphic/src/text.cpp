#include "text.h"
#include "log.h"

Text_editor::Text_editor(int size, const std::string& font_file, gi::Color color) :
	font_file(font_file),
	font(gi::Font::generate()),
	text(gi::Text::generate())
{
	if (!font->load(font_file))
		Log::add("text_editor", "cant load font: " + font_file);
	text->set_font(font);
	text->set_size(size);
	text->set_color(color);
}

gi::Text* Text_editor::generate(const std::string& string, gi::Vector position)
{
	gi::Text* ans = text->copy();
	ans->set_text(string);
	ans->set_position(position);
	return ans;
}

void Text_editor::set_text(gi::Text* pattern)
{
	delete text;
	text = pattern;
}

void Text_editor::set_font(const std::string& file_name)
{
	font->load(file_name);
	text->set_font(font);
}

int Text_editor::get_number_line(const std::string& string)
{
	int ans = 1;
	for (auto it : string)
		if (it == '\n')
			++ans;
	return ans;
}

int Text_editor::get_length_line(const std::string& string)
{
	int ans = 0;
	int find = 0;
	for (auto it : string)
		if (it == '\n')
			ans = std::max(ans, find), find = 0;
		else
			++find;
	return std::max(ans, find);
}

const std::vector<std::string> Text::names = std::vector<std::string>
{
	"title",
	"text",
	"offer",
	"offer small"
};

std::vector<std::shared_ptr<Text_editor>> Text::patterns = std::vector<std::shared_ptr<Text_editor>>
{
	std::shared_ptr<Text_editor>(new Text_editor(30, "../data/font.ttf")),
	std::shared_ptr<Text_editor>(new Text_editor(25, "../data/font.ttf", gi::Color(0, 0, 0))),
	std::shared_ptr<Text_editor>(new Text_editor(20, "../data/font.ttf", gi::Color(0, 0, 0))),
	std::shared_ptr<Text_editor>(new Text_editor(25, "../data/font.ttf", gi::Color(0, 0, 0)))
};

gi::Text* Text::generate(Type type, const std::string& text, gi::Vector position)
{
	return patterns[type]->generate(text, position);
}