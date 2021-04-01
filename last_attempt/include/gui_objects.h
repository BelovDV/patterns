#pragma once

#include <SFML/Graphics.hpp>

namespace Gui_objects
{
	enum Position_type
	{
		left_up,
		left_down,
		right_up,
		right_down,
		exact_centre,
		shifting_space,
		count_of_types
	};
	class Object : public sf::Drawable
	{
	public:
		Object(Position_type type, int number);
	public:
		sf::FloatRect get_area() const { return area; }
		virtual void set_position(sf::Vector2f pos) = 0;
		bool contain(sf::Vector2i pos) const { return get_area().contains(static_cast<sf::Vector2f>(pos)); }
		bool contain(sf::Vector2f pos) const { return get_area().contains(pos); }
		int get_number() { return number_in_position; }
		Position_type get_pos_type() { return pos_type; }
		Object& operator*() { return *this; }
		const Object& operator*() const { return *this; }
	protected:
		sf::Vector2f position;
		int number_in_position;
		Position_type pos_type;
		sf::FloatRect area;
	};
	class Executable
	{
	public:
		Executable(int id) : id(id) {}
	public:
		int get_id() { return id; }
		virtual void select_on() = 0;
		virtual void select_off() = 0;
	private:
		int id;
	};
	class Label : public Object
	{
	public:
		enum Back_type
		{
			none
		};
	public:
		Label(Position_type position, int number, sf::Text text);
		Label(Position_type position, int number, sf::Text text, sf::FloatRect area, Back_type type = none);
	public:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		virtual void set_position(sf::Vector2f pos) override;
		const sf::Text& get_text() { return text; }
	protected:
		sf::Text text;
		Back_type type;
	};
	class Button : public Label, public Executable
	{
	public:
		Button(Position_type position, int number, int id, sf::Text text);
		Button(Position_type position, int number, int id, sf::Text text, sf::FloatRect area, Back_type type = none);
	public:
		void select_on() override { text.setColor(sf::Color::Green); }
		void select_off() override { text.setColor(sf::Color::Black); }
	private:
	};
	class Input : public Object {};
	class List_objects : public Object
	{
	public:
		List_objects(Position_type position, int number, Object* head, std::vector<Object*>&& objects);
	public:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		virtual void set_position(sf::Vector2f pos) override;
	private:
		Object* head;
		std::vector<Object*> objects;
	};
}