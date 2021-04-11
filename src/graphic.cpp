#include "../include/graphic.h"

Graphic::Graphic() :
	window(sf::VideoMode(1820, 1080), "", sf::Style::None)
{
	window.setPosition(sf::Vector2i(0, 0));
}

void Graphic::display()
{
	window.display();
}

bool Graphic::is_open()
{
	return window.isOpen();
}

bool Graphic::poll_event(gi::Event& event)
{
	event.type = gi::Event_type::none;
	sf::Event vsp;
	bool ans = window.pollEvent(vsp);
	if (!ans)
		return false;
	if (vsp.type == sf::Event::EventType::MouseMoved)
		event.type = gi::Event_type::mouse_moved;
	else if (vsp.type == sf::Event::EventType::MouseButtonPressed)
		event.type = gi::Event_type::mouse_button_pressed;
	else if (vsp.type == sf::Event::EventType::KeyPressed)
	{
		event.type = gi::Event_type::key_pressed;
		event.keycode = static_cast<int>(vsp.key.code);

		if (event.keycode == sf::Keyboard::Escape)
			window.close();
	}
	return true;
}

gi::Vector Graphic::get_mouse_position()
{
	auto ans = sf::Mouse::getPosition();
	return gi::Vector(ans.x, ans.y);
}

gi::Texture* gi::Texture::generate()
{
	return new ::Texture();
}

gi::Font* gi::Font::generate()
{
	return new ::Font();
}

gi::Sprite* gi::Sprite::generate()
{
	return new ::Sprite;
}

gi::Text* gi::Text::generate()
{
	return new Text_wrapper;
}

gi::Shape_rect* gi::Shape_rect::generate()
{
	return new ::Shape_rect;
}

gi::Rect Text_wrapper::get_bounds() const
{
	auto vsp = text.getGlobalBounds();
	gi::Rect ans(vsp.left, vsp.top, vsp.width, vsp.height);
	return ans;
}

void Text_wrapper::set_font(gi::Font* font)
{
	text.setFont(dynamic_cast<sf::Font&>(*font));
}

bool Texture::load(const std::string& file)
{
	return loadFromFile(file);
}

bool Font::load(const std::string& file)
{
	return loadFromFile(file);
}

void Sprite::draw(Graphic_interface& window) const
{
	dynamic_cast<Graphic&>(window).draw(*this);
}

void Sprite::set_position(gi::Vector position)
{
	setPosition(position.x, position.y);
}

void Sprite::set_texture(const gi::Texture& texture)
{
	setTexture(dynamic_cast<const sf::Texture&>(texture));
}

void Shape_rect::draw(Graphic_interface& window) const
{
	sf::RectangleShape vsp(sf::Vector2f(area.width, area.height));
	vsp.move(sf::Vector2f(area.left, area.top));
	vsp.setFillColor(inner_color);
	vsp.setOutlineColor(outline_color);
	vsp.setOutlineThickness(1);
	dynamic_cast<Graphic&>(window).draw(vsp);
}

void Shape_rect::set_inner_color(gi::Color color)
{
	inner_color = sf::Color(color.r, color.g, color.b, color.a);
}

void Shape_rect::set_outline_color(gi::Color color)
{
	outline_color = sf::Color(color.r, color.g, color.b, color.a);
}