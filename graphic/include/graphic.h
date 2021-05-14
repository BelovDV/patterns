#pragma once

#include "graphic_interface.h"
#include "window_interface.h"

#include <SFML/Graphics.hpp>

class Window : public Window_interface
{
public:
	Window(int width, int heigh);
public:
	virtual void display() override;
	virtual bool is_open() override;
	virtual bool poll_event(gi::Event& event) override;
	virtual gi::Vector get_mouse_position() override;
	virtual void set_screen(gi::Rect rect) override;
	virtual gi::Vector get_screen_size() override;
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
	virtual void set_color(gi::Color c) override { text.setFillColor(sf::Color(c.r, c.g, c.b)); }
	virtual void set_text(const std::string& string) override { text.setString(string); }
	virtual void draw(Window_interface& window) const override { dynamic_cast<Window*>(&window)->draw(text); }
	//virtual const std::string get_text() const override { return std::string(text.getString()); }
public:
	sf::Text text;
};

class Texture : public gi::Texture, public sf::Texture
{
	virtual bool load(const std::string& file) override;
	virtual gi::Vector size() const override;
};

class Font : public gi::Font, public sf::Font
{
	virtual bool load(const std::string& file) override;
};

class Sprite : public gi::Sprite, public sf::Sprite
{
	virtual void set_texture(const gi::Texture& texture) override;
	virtual void draw(Window_interface& window) const override;
	virtual void set_position(gi::Vector position) override;
	virtual void set_scale(double x_scale, double y_scale) override;
	virtual void set_texture_rect(gi::Rect rect) override;
};

class Shape_rect : public gi::Shape_rect
{
	virtual void draw(Window_interface& window) const override;
	virtual void set_inner_color(gi::Color color) override;
	virtual void set_outline_color(gi::Color color) override;
private:
	sf::Color inner_color;
	sf::Color outline_color;
};