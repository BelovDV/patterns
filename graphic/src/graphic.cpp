#include "graphic.h"

Window::Window(int x, int y) :
	window(sf::VideoMode(x, y), "", sf::Style::None)
{
	window.setPosition(sf::Vector2i(0, 0));
}

void Window::display()
{
	window.display();
}

bool Window::is_open()
{
	return window.isOpen();
}

bool Window::poll_event(gi::Event& event)
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

gi::Vector Window::get_mouse_position()
{
	auto ans = sf::Mouse::getPosition();
	auto delta = window.getPosition();
	ans -= delta;
	return gi::Vector(ans.x, ans.y);
}

void Window::set_screen(gi::Rect rect)
{
	window.create(sf::VideoMode(rect.width, rect.height), "", sf::Style::None);
	window.setPosition(sf::Vector2i(rect.left, rect.top));
}

gi::Vector Window::get_screen_size()
{
	auto size = window.getSize();
	return gi::Vector(size.x, size.y);
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

gi::Vector Texture::size() const
{
	return gi::Vector(this->getSize().x, this->getSize().y);
}

bool Font::load(const std::string& file)
{
	return loadFromFile(file);
}

void Sprite::draw(Window_interface& window) const
{
	dynamic_cast<Window&>(window).draw(*this);
}

void Sprite::set_position(gi::Vector position)
{
	setPosition(position.x, position.y);
}

void Sprite::set_texture(const gi::Texture& texture)
{
	setTexture(dynamic_cast<const sf::Texture&>(texture));
}

void Sprite::set_scale(double x_scale, double y_scale)
{
	setScale(sf::Vector2f(x_scale, y_scale));
}

void Sprite::set_texture_rect(gi::Rect rect)
{
	this->setTextureRect(sf::IntRect(rect.left, rect.top, rect.width, rect.height));
}

void Shape_rect::draw(Window_interface& window) const
{
	sf::RectangleShape vsp(sf::Vector2f(area.width, area.height));
	vsp.move(sf::Vector2f(area.left, area.top));
	vsp.setFillColor(inner_color);
	vsp.setOutlineColor(outline_color);
	vsp.setOutlineThickness(1);
	dynamic_cast<Window&>(window).draw(vsp);
}

void Shape_rect::set_inner_color(gi::Color color)
{
	inner_color = sf::Color(color.r, color.g, color.b, color.a);
}

void Shape_rect::set_outline_color(gi::Color color)
{
	outline_color = sf::Color(color.r, color.g, color.b, color.a);
}