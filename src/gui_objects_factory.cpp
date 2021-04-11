#include "../include/gui_objects_factory.h"
#include "../include/gui_objects_concrete.h"
#include "../include/log.h"

gi::Label* Gui_objects_basic_factory::get_label(gi::Position_type position, gi::Text* text)
{
	return new gi_c::basic::Label(position, text);
}

gi::Button* Gui_objects_basic_factory::get_button(gi::Position_type position, int id, gi::Text* text)
{
	return new gi_c::basic::Button(position, id, text);
}

gi::Button* Gui_objects_basic_factory::get_button(gi::Position_type position, int id, gi::Text* text, gi::Rect rect)
{
	return new gi_c::basic::Button(position, id, text, rect);
}

gi::List_objects* Gui_objects_basic_factory::get_list_objects(gi::Position_type position, std::vector<gi::Object*>&& objects)
{
	return new gi_c::basic::List_objects(position, std::move(objects));
}

gi::Label* Gui_objects_logging_factory::get_label(gi::Position_type position, gi::Text* text)
{
	Log::add("factory", "create label");
	return new gi_c::logging::Label(position, text);
}

gi::Button* Gui_objects_logging_factory::get_button(gi::Position_type position, int id, gi::Text* text)
{
	Log::add("factory", "create button");
	return new gi_c::logging::Button(position, id, text);
}

gi::Button* Gui_objects_logging_factory::get_button(gi::Position_type position, int id, gi::Text* text, gi::Rect rect)
{
	Log::add("factory", "create button");
	return new gi_c::logging::Button(position, id, text, rect);
}

gi::List_objects* Gui_objects_logging_factory::get_list_objects(gi::Position_type position, std::vector<gi::Object*>&& objects)
{
	Log::add("factory", "create list");
	return new gi_c::logging::List_objects(position, std::move(objects));
}

Gui_objects_backtexture_factory::Gui_objects_backtexture_factory(const std::string& file) : 
	background(gi::Texture::generate())
{
	background->load(file);
}

gi::Label* Gui_objects_backtexture_factory::get_label(gi::Position_type position, gi::Text* text)
{
	return new gi_c::bactexture::Label(position, text, background);
}

gi::Button* Gui_objects_backtexture_factory::get_button(gi::Position_type position, int id, gi::Text* text)
{
	return new gi_c::bactexture::Button(position, id, text);
}

gi::Button* Gui_objects_backtexture_factory::get_button(gi::Position_type position, int id, gi::Text* text, gi::Rect rect)
{
	return new gi_c::bactexture::Button(position, id, text, rect);
}

gi::List_objects* Gui_objects_backtexture_factory::get_list_objects(gi::Position_type position, std::vector<gi::Object*>&& objects)
{
	return new gi_c::bactexture::List_objects(position, std::move(objects));
}