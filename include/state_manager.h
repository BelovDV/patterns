#pragma once

#include "interactive_fiction.h"
#include "beginning.h"
#include "start_menu.h"

class State_manager : public Gui_interface
{
public:
    State_manager(Beginning* beg, Start_menu* start);
public:
    void get_targets(Target_form& form) override;
    void set_event(int id) override;
    Condition get_condition() override;
private:
    Gui_interface* beginning;
    Gui_interface* start_menu;
    Gui_interface* worker;
    Condition condition = none;
};