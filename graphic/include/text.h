#pragma once

#include "graphic_interface.h"

#include <vector>
#include <string>
#include <memory>

class Text_editor
{
public:
	Text_editor(int size, const std::string& font_file, gi::Color color = gi::Color(0, 0, 0));
public:
	gi::Text* generate(const std::string& text, gi::Vector position = gi::Vector(0, 0));
	void set_text(gi::Text* pattern);
	void set_font(const std::string& file_name);
	void set_size(int size) { text->set_size(size); }
	int get_size() { return text->get_size(); }
	const gi::Text& get_text() { return *text; }
	int get_number_line(const std::string& string);
	int get_length_line(const std::string& string);
	const std::string& get_font_file() { return font_file; }
private:
	gi::Text* text;
	gi::Font* font;
	std::string font_file;
};

namespace Text
{
	enum Type
	{
		title,
		text,
		offer,
		offer_small,
		overall_count
	};
	
	const extern std::vector<std::string> names;
	extern std::vector<std::shared_ptr<Text_editor>> patterns;
	
	gi::Text* generate(Type type, const std::string& text, gi::Vector position = gi::Vector(0, 0));
}