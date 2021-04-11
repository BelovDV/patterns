#pragma once

#include "graphic_interface.h"

#include <SFML/Graphics.hpp>

class Graphic : public Graphic_interface
{
public:
	Graphic();
public:
	virtual void display() override;
	virtual bool is_open() override;
	virtual bool poll_event(gi::Event& event) override;
	virtual gi::Vector get_mouse_position() override;
public:
	void draw(const sf::Drawable& object) { window.draw(object); }
private:
	sf::RenderWindow window;
};

class Text_wrapper : public gi::Text
{
public:

public:
	virtual gi::Text* copy() override{ return new Text_wrapper(*this); }
public:
	virtual void set_size(int size) override { text.setCharacterSize(size); }
	virtual void set_position(gi::Vector pos) override { text.setPosition(pos.x, pos.y); }
	virtual gi::Rect get_bounds() const override;
	virtual int get_size() const override { return text.getCharacterSize(); }
	virtual void set_font(gi::Font* font) override;
	virtual void set_color(gi::Color c) override { text.setColor(sf::Color(c.r, c.g, c.b)); }
	virtual void set_text(const std::string& string) override { text.setString(string); }
	virtual void draw(Graphic_interface& window) const override { dynamic_cast<Graphic*>(&window)->draw(text); }
public:
	sf::Text text;
};

class Texture : public gi::Texture, public sf::Texture
{
	virtual bool load(const std::string& file) override;
};

class Font : public gi::Font, public sf::Font
{
	virtual bool load(const std::string& file) override;
};

class Sprite : public gi::Sprite, public sf::Sprite
{
	virtual void set_texture(const gi::Texture& texture) override;
	virtual void draw(Graphic_interface& window) const override;
	virtual void set_position(gi::Vector position) override;
};

class Shape_rect : public gi::Shape_rect
{
	virtual void draw(Graphic_interface& window) const override;
	virtual void set_inner_color(gi::Color color) override;
	virtual void set_outline_color(gi::Color color) override;
private:
	sf::Color inner_color;
	sf::Color outline_color;
};