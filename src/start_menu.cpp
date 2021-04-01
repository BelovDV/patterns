#include <cstdlib>

#include "../include/start_menu.h"

using namespace Gui_objects;

Start_menu::Start_menu(Settings& settings) :
	Interactive_fiction("../data/cond.txt"),
	settings(settings)
{}

void Start_menu::options_screen()
{

}

void Start_menu::options_fonts()
{
	Text::Type type;
	auto& vsp = last_condition;
	if (*vsp[0] == Text::names[Text::Type::offer])
		type = Text::Type::offer;
	else if (*vsp[0] == Text::names[Text::Type::offer_small])
		type = Text::Type::offer_small;
	else if (*vsp[0] == Text::names[Text::Type::text])
		type = Text::Type::text;
	else if (*vsp[0] == Text::names[Text::Type::title])
		type = Text::Type::title;
	else
		return;

	if (std::to_string(std::atoi(vsp[1]->c_str())) == *vsp[1])
		settings.set_text_size(type, std::atoi(vsp[1]->c_str()));

	if (*vsp[2] == "first")
		settings.set_font(type, "../data/font.ttf");
	if (*vsp[2] == "second")
		settings.set_font(type, "../data/second.ttf");

	forget();
}

void Start_menu::get_targets(Gui_interface::Target_form& form)
{
	auto space = Position_type::shifting_space;
	auto& current = conditions[position];
	auto& ways = current.ways;
	if (position == "main")
		form.add(new Label(space, -1, Text::generate(Text::title, current.message)));
	else
		form.add(new Label(space, -1, Text::generate(Text::text, current.message)));

	for (int i = 0; i != ways.size(); ++i)
		form.add(new Button(space, i, i, Text::generate(Text::offer, ways[i].name)));
	int delta = ways.size();
	for (int i = 0; i != current.lists.size(); ++i)
	{
		form.add(new Button(space, i + delta, i + delta, Text::generate(Text::offer, *condition[i])));
		if (i == chosen_list && ++delta)
			for (int j = 0; j != current.lists[chosen_list].values.size(); ++j, ++delta)
				form.add(new Button(space, i + delta, i + delta, Text::generate(Text::offer_small, current.lists[chosen_list].values[j])));
	}
}

void Start_menu::set_event(int id)
{
	press(id);

	if (last_target_name == "apply")
	{
		if (position == "screen")
			options_screen();
		else if (position == "fonts")
			options_fonts();
	}

	if (position == "exit")
		gui_condition = Gui_interface::Condition::exit;
	else
		gui_condition = Gui_interface::Condition::none;
}