#pragma once

#include "gui_objects.h"
#include "log.h"

#include<cstdlib>

namespace gi_c
{
	namespace basic
	{
		class Label : public gi::Label
		{
		public:
			Label(gi::Position_type position, gi::Text* text);
		public:
			virtual void draw(Window_interface& window) const override;
			virtual const gi::Text& get_text() const override { return *text; }
			virtual void set_position(gi::Vector position) override;
		protected:
			gi::Text* text;
		};
		class Button : public gi::Button
		{
		public:
			Button(gi::Position_type position, int id, gi::Text* text);
			Button(gi::Position_type position, int id, gi::Text* text, gi::Rect area);
		public:
			void select_on() override;
			void select_off() override;
			virtual void draw(Window_interface& window) const override;
			virtual const gi::Text& get_text() const override { return *text; }
			virtual void set_position(gi::Vector position) override;
		protected:
			gi::Text* text;
		};
		class List_objects : public gi::List_objects
		{
		public:
			List_objects(gi::Position_type position, std::vector<Object*>&& objects);
		public:
			virtual void draw(Window_interface& window) const override;
			virtual void set_position(gi::Vector pos) override;
		private:
			std::vector<Object*> objects;
		};
	}
	namespace logging
	{
		class Label : public basic::Label
		{
		public:
			Label(gi::Position_type position, gi::Text* text) :
				basic::Label(position, text)
			{
				static int counter = 0;
				Log::add("label_test", std::to_string(++counter));
			}
			~Label()
			{
				static int counter = 0;
				Log::add("label_test_destruct", std::to_string(++counter));
			}
		public:
		};
		class Button : public basic::Button
		{
		public:
			Button(gi::Position_type position, int id, gi::Text* text) :
				basic::Button(position, id, text) 
			{
				static int counter = 0;
				Log::add("button_test", std::to_string(++counter));
			}
			Button(gi::Position_type position, int id, gi::Text* text, gi::Rect area) : 
				Button(position, id, text) 
			{
				this->area = area;
			}
			~Button()
			{
				static int counter = 0;
				Log::add("button_test_destruct", std::to_string(++counter));
			}
		public:
		};
		class List_objects : public basic::List_objects
		{
		public:
			List_objects(gi::Position_type position, std::vector<Object*>&& objects) :
				basic::List_objects(position, std::move(objects))
			{
				static int counter = 0;
				Log::add("list_test", std::to_string(++counter));
			}
			~List_objects()
			{
				static int counter = 0;
				Log::add("list_test_destruct", std::to_string(++counter));
			}
		public:
		};
	}
	namespace rect
	{
		class Label : public basic::Label
		{
		public:
			Label(gi::Position_type position, gi::Text* text) : basic::Label(position, text) {}
		};
		class Button : public basic::Button
		{
		public:
			Button(gi::Position_type position, int id, gi::Text* text) : basic::Button(position, id, text) {}
			Button(gi::Position_type position, int id, gi::Text* text, gi::Rect area) : basic::Button(position, id, text, area) {}
		public:
			virtual void draw(Window_interface& window) const override;
		};
		class List_objects : public basic::List_objects
		{
		public:
			List_objects(gi::Position_type position, std::vector<Object*>&& objects) : basic::List_objects(position, std::move(objects)) {}
		};
	}
	namespace bactexture
	{
		class Label : public basic::Label
		{
		public:
			Label(gi::Position_type position, gi::Text* text, gi::Texture* texture) :
				basic::Label(position, text),
				texture_size(texture->size())
			{
				sprite = gi::Sprite::generate();
				sprite->set_texture(*texture);
				sprite->set_scale(get_area().width / (double)texture_size.x, get_area().height / (double)texture_size.y);
			}
			~Label()
			{
				delete sprite;
			}
		public:
			virtual void draw(Window_interface& window) const override
			{
				sprite->draw(window);
				basic::Label::draw(window);
			}
			virtual void set_position(gi::Vector position) override
			{
				auto todo = position;
				todo.y += 8;
				sprite->set_position(todo);
				sprite->set_scale(get_area().width / (double)texture_size.x, get_area().height / (double)texture_size.y);
				basic::Label::set_position(position);
			}

		private:
			gi::Sprite* sprite;
			gi::Vector texture_size;
		};
		class Button : public basic::Button
		{
		public:
			Button(gi::Position_type position, int id, gi::Text* text) :
				basic::Button(position, id, text)
			{}
			Button(gi::Position_type position, int id, gi::Text* text, gi::Rect area) :
				basic::Button(position, id, text, area)
			{}
		public:
		};
		class List_objects : public basic::List_objects
		{
		public:
			List_objects(gi::Position_type position, std::vector<Object*>&& objects) :
				basic::List_objects(position, std::move(objects))
			{}
		public:
		};
	}
}