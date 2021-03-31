#pragma once

#include <SFML/Graphics.hpp>

class Text_editor
{
public:
	Text_editor(int size, const std::string& font_file, sf::Color color = sf::Color::Black, bool italic = false, bool bold = false);
public:
	sf::Text generate(const std::string& text, sf::Vector2i position);
	sf::Text generate(const std::string& text, sf::Vector2i position, sf::Color color, bool italic, bool bold);
	void set_text(sf::Text pattern) { text = pattern; }
	void set_font(const std::string& file_name);
	void set_size(int size) { text.setCharacterSize(size); }
	const sf::Text& get_text() { return text; }
	int get_number_line(const std::string& string);
	int get_length_line(const std::string& string);
	int get_size() { return text.getCharacterSize(); }
private:
	sf::Text text;
	sf::Font font;
};

namespace Text
{
	extern Text_editor title;
	extern Text_editor text;
	extern Text_editor offer;

	enum text_list_name
	{
		e_title,
		e_text,
		e_offer
	};

	const std::vector<Text_editor*> text_list =
	{
		&title,
		&text,
		&offer
	};
}