#pragma once

#include "interactive_fiction.h"
#include "gui_interface.h"
#include "gui_objects_factory.h"
#include "position.h"

class Beginning : public Interactive_fiction, public Gui_interface
{
public:
    explicit Beginning(Gui_objects_abstract_factory* factory, Position* pos);
private:
    Gui_interface::Condition get_condition() override { return gui_condition; }
	void get_targets(Gui_interface::Target_form& form) override;
	void set_event(int id) override;
private:
	Gui_interface::Condition gui_condition = Gui_interface::none;
	Gui_objects_abstract_factory* factory;
	Position* game_position;
	std::vector<int> p_money = std::vector<int>({200, 100, 75});
};