#pragma once

#include "gui_objects.h"

class Gui_objects_abstract_factory
{
public:
	enum Type
	{
		basic,
		logging,
		backtexture
	};
public:
	virtual gi::Label* get_label(gi::Position_type position, gi::Text* text) = 0;
	virtual gi::Button* get_button(gi::Position_type position, int id, gi::Text* text) = 0;
	virtual gi::Button* get_button(gi::Position_type position, int id, gi::Text* text, gi::Rect rect) = 0;
	virtual gi::List_objects* get_list_objects(gi::Position_type position, std::vector<gi::Object*>&& objects) = 0;
private:
	Gui_objects_abstract_factory* factory = nullptr;
};

class Gui_objects_basic_factory : public Gui_objects_abstract_factory
{
	virtual gi::Label* get_label(gi::Position_type position, gi::Text* text) override;
	virtual gi::Button* get_button(gi::Position_type position, int id, gi::Text* text) override;
	virtual gi::Button* get_button(gi::Position_type position, int id, gi::Text* text, gi::Rect rect) override;
	virtual gi::List_objects* get_list_objects(gi::Position_type position, std::vector<gi::Object*>&& objects) override;
};

class Gui_objects_logging_factory : public Gui_objects_abstract_factory
{
	virtual gi::Label* get_label(gi::Position_type position, gi::Text* text) override;
	virtual gi::Button* get_button(gi::Position_type position, int id, gi::Text* text) override;
	virtual gi::Button* get_button(gi::Position_type position, int id, gi::Text* text, gi::Rect rect) override;
	virtual gi::List_objects* get_list_objects(gi::Position_type position, std::vector<gi::Object*>&& objects) override;
};

class Gui_objects_backtexture_factory : public Gui_objects_abstract_factory
{
public:
	Gui_objects_backtexture_factory(const std::string& file);
	~Gui_objects_backtexture_factory() { delete background; }
private:
	virtual gi::Label* get_label(gi::Position_type position, gi::Text* text) override;
	virtual gi::Button* get_button(gi::Position_type position, int id, gi::Text* text) override;
	virtual gi::Button* get_button(gi::Position_type position, int id, gi::Text* text, gi::Rect rect) override;
	virtual gi::List_objects* get_list_objects(gi::Position_type position, std::vector<gi::Object*>&& objects) override;
private:
	gi::Texture* background;
};