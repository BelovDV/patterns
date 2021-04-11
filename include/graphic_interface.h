#pragma once

#include <string>

class Graphic_interface;

namespace gi
{
	enum Event_type
	{
		none,
		mouse_moved,
		mouse_button_pressed,
		key_pressed
	};
	struct Event
	{
		Event_type type;
		union
		{
			int keycode;
		};
	};
	struct Vector
	{
		Vector(int x = 0, int y = 0) : x(x), y(y) {}
		int x, y;
	};
	struct Rect
	{
		Rect(int l = 0, int t = 0, int w = 0, int h = 0) : 
			left(l), top(t), width(w), height(h) 
		{}
		int left;
		int top;
		int width;
		int height;
		bool contain(Vector vec) const
		{
			return
				vec.x >= left && vec.x <= left + width &&
				vec.y >= top && vec.y <= top + height;
		}
	};
	struct Color
	{
		Color(int r, int g, int b, int a = 255) : r(r), g(g), b(b), a(a) {}
		int r, g, b, a;
	};

	class Texture 
	{
	public:
		static Texture* generate();
		virtual bool load(const std::string& file) = 0;
	};
	class Font
	{
	public:
		static Font* generate();
		virtual bool load(const std::string& file) = 0;
	};

	class Drawable
	{
	public:
		virtual void draw(Graphic_interface& window) const = 0;
	};
}

class Graphic_interface
{
public:
	
public:
	Graphic_interface& operator*() { return *this; }
	const Graphic_interface& operator*() const { return *this; }
public:
	virtual void display() = 0;
	virtual bool is_open() = 0;
	virtual bool poll_event(gi::Event& event) = 0;
	virtual gi::Vector get_mouse_position() = 0;
};

namespace gi
{
	class Text : public Drawable
	{
	public:
		static Text* generate();
		virtual Text* copy() = 0;
	public:
		virtual void set_size(int size) = 0;
		virtual void set_position(Vector pos) = 0;
		virtual Rect get_bounds() const = 0;
		virtual int get_size() const = 0;
		virtual void set_font(Font* font) = 0;
		virtual void set_color(Color) = 0;
		virtual void set_text(const std::string& text) = 0;
		virtual void draw(Graphic_interface& window) const = 0;
	};
	class Sprite : public Drawable
	{
	public:
		static Sprite* generate();
	public:
		virtual void set_texture(const Texture& texture) = 0;
		virtual void draw(Graphic_interface& window) const = 0;
		virtual void set_position(Vector position) = 0;
	};
	class Shape_rect : public Drawable
	{
	public:
		static Shape_rect* generate();
	public:
		virtual void draw(Graphic_interface& window) const = 0;
		virtual void set_inner_color(gi::Color color) = 0;
		virtual void set_outline_color(gi::Color color) = 0;
		void set_rect(Rect rect) { area = rect; }
	protected:
		Rect area;
	};
}