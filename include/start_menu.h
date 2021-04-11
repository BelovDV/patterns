#pragma once

#include "interactive_fiction.h"
#include "settings.h"
#include "gui.h"
#include "gui_interface.h"
#include "text.h"

class Start_menu : Interactive_fiction, public Gui_interface
{
public:
	Start_menu(Settings& settings);
private:
	void options_screen();
	void options_fonts();
	virtual Gui_interface::Condition get_condition() override { return gui_condition; }
	virtual void get_targets(Gui_interface::Target_form& form) override;
	virtual void set_event(int id) override;
private:
	Settings& settings;
	Gui_interface::Condition gui_condition = Gui_interface::none;
};