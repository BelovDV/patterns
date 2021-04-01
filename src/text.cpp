#include "../include/text.h"
#include "../include/log.h"

Text_editor::Text_editor(int size, const std::string& font_file, sf::Color color, bool italic, bool bold) :
	font_file(font_file)
{
	if (!font.loadFromFile(font_file))
		Log::add("text_editor", "cant load font: " + font_file);
	text.setFont(font);
	text.setCharacterSize(size);
	text.setColor(color);
	if (italic)
		text.setStyle(sf::Text::Style::Italic);
	if (bold)
		text.setStyle(sf::Text::Style::Bold);
}

sf::Text Text_editor::generate(const std::string& string, sf::Vector2i position)
{
	sf::Text ans = text;
	ans.setString(string);
	ans.move(position.x, position.y);
	return ans;
}

sf::Text Text_editor::generate(const std::string& string, sf::Vector2i position, sf::Color color, bool italic, bool bold)
{
	sf::Text ans = text;
	ans.setString(string);
	ans.move(position.x, position.y);
	ans.setColor(color);
	if (italic)
		ans.setStyle(sf::Text::Style::Italic);
	if (bold)
		ans.setStyle(sf::Text::Style::Bold);
	return ans;
}

void Text_editor::set_font(const std::string& file_name)
{
	font.loadFromFile(file_name);
	text.setFont(font);
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
	std::shared_ptr<Text_editor>(new Text_editor(25, "../data/font.ttf", sf::Color::Black, true)),
	std::shared_ptr<Text_editor>(new Text_editor(20, "../data/font.ttf", sf::Color::Black, true)),
	std::shared_ptr<Text_editor>(new Text_editor(25, "../data/font.ttf", sf::Color::Black))
};

sf::Text Text::generate(Type type, const std::string& text, sf::Vector2i position)
{
	return patterns[type]->generate(text, position);
}

sf::Text Text::generate(Type type, const std::string& text, sf::Vector2i position, sf::Color color, bool italic, bool bold)
{
	return patterns[type]->generate(text, position, color, italic, bold);
}