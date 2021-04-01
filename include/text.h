#pragma once

#include <SFML/Graphics.hpp>

class Text_editor
{
public:
	Text_editor(int size, const std::string& font_file, sf::Color color = sf::Color::Black, bool italic = false, bool bold = false);
public:
	sf::Text generate(const std::string& text, sf::Vector2i position = sf::Vector2i(0, 0));
	sf::Text generate(const std::string& text, sf::Vector2i position, sf::Color color, bool italic, bool bold);
	void set_text(sf::Text pattern) { text = pattern; }
	void set_font(const std::string& file_name);
	void set_size(int size) { text.setCharacterSize(size); }
	const sf::Text& get_text() { return text; }
	int get_number_line(const std::string& string);
	int get_length_line(const std::string& string);
	int get_size() { return text.getCharacterSize(); }
	const std::string& get_font_file() { return font_file; }
private:
	sf::Text text;
	sf::Font font;
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
	
	sf::Text generate(Type type, const std::string& text, sf::Vector2i position = sf::Vector2i(0, 0));
	sf::Text generate(Type type, const std::string& text, sf::Vector2i position, sf::Color color, bool italic, bool bold);
}