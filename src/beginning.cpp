#include "beginning.h"
#include "text.h"
#include "log.h"
#include "database_loader.h"

Beginning::Beginning(Gui_objects_abstract_factory* factory, Position* pos) :
    Interactive_fiction("../data/dialogs/beginning"),
    factory(factory),
    game_position(pos)
{}

void Beginning::get_targets(Gui_interface::Target_form& form)
{
    auto space = gi::Position_type::shifting_space;
	auto& current = conditions[position];
	auto& ways = current.ways;

    form.add(factory->get_label(space, Text::generate(Text::title, current.message)));

    if (position != "troops") {
        for (int i = 0; i != ways.size(); ++i)
            form.add(factory->get_button(space, i, Text::generate(Text::offer, ways[i].name)));
        //form.add(new gi::Button(space, i, Text::generate(Text::offer, ways[i].name)));
        int delta = ways.size();
        for (int i = 0; i != current.lists.size(); ++i) {
            form.add(factory->get_button(space, i + delta, Text::generate(Text::offer, *condition[i])));
            //form.add(new gi::Button(space, i + delta, Text::generate(Text::offer, *condition[i])));
            if (i == chosen_list && ++delta)
                for (int j = 0; j != current.lists[chosen_list].values.size(); ++j, ++delta)
                    form.add(factory->get_button(space, i + delta, Text::generate(Text::offer_small,
                                                                                  current.lists[chosen_list].values[j])));
            //form.add(new gi::Button(space, i + delta, Text::generate(Text::offer_small, current.lists[chosen_list].values[j])));
        }
    }
    else
    {
        auto bought = game_position->get_count_list_units(Position::player1);
        for (auto& it : bought)
            form.add(factory->get_label(space, Text::generate(Text::offer,
                    database.get_units()[it.first].name + " " + std::to_string(it.second))));
        const auto& u_id = database.get_races_units()[game_position->get_race(Position::player1)];
        const auto& u_ref = database.get_units();
//        for (int i = 0; i != u_id.size(); ++i)
//            form.add(factory->get_label(space, Text::generate(Text::offer,
//                    u_ref[u_id[i]].name + "\talready"
//                    )));
        form.add(factory->get_label(space, Text::generate(Text::offer,
                    "money A " + std::to_string(p_money[0]))));
        form.add(factory->get_label(space, Text::generate(Text::offer,
                                                          "money B " + std::to_string(p_money[1]))));
        form.add(factory->get_label(space, Text::generate(Text::offer,
                                                          "money D " + std::to_string(p_money[2]))));
        // "D not bug but feature"
        for (int i = 0; i != u_id.size(); ++i)
            form.add(factory->get_button(space, i,Text::generate(Text::offer,
                u_ref[u_id[i]].name + "\t" +
                std::to_string(u_ref[u_id[i]].cost_A) + " " +
                std::to_string(u_ref[u_id[i]].cost_B) + " " +
                std::to_string(u_ref[u_id[i]].cost_C))));
        form.add(factory->get_button(space, u_id.size() + 0, Text::generate(Text::offer, "reset")));
        form.add(factory->get_button(space, u_id.size() + 1, Text::generate(Text::offer, "ready")));
        form.add(factory->get_button(space, u_id.size() + 2, Text::generate(Text::offer, "back")));
    }
}

void Beginning::set_event(int id)
{
    if (position == "troops" && id < database.get_races_units()[game_position->get_race(Position::player1)].size())
    {
        int u_id = database.get_races_units()[game_position->get_race(Position::player1)][id];
        const Data::Unit::Data& unit_data = database.get_units()[u_id];
        if (p_money[0] >= unit_data.cost_A && p_money[1] >= unit_data.cost_B && p_money[2] >= unit_data.cost_C)
        {
            p_money[0] -= unit_data.cost_A;
            p_money[1] -= unit_data.cost_B;
            p_money[2] -= unit_data.cost_C;
            auto race = game_position->get_race(Position::player1);
            game_position->add_unit(Position::player1, Unit(database.get_races_units()[race][id]));
        }
    }
    if (position == "troops")
    {
        if (id >= database.get_races_units()[game_position->get_race(Position::player1)].size())
            press(id - database.get_races_units()[game_position->get_race(Position::player1)].size());
    }
    else
        press(id);
    if (position == "troops" && (last_target_name == "reset" || last_position == "troops")) {
        last_target_name = "none";
        last_position = "none";
        game_position->reset(Position::player1);
        auto& c_data = database.get_classes()[id - database.get_races_units()[game_position->get_race(Position::player1)].size()];
        p_money[0] = c_data.start_money_A;
        p_money[1] = c_data.start_money_B;
        p_money[2] = c_data.start_money_C;
    }
    if (position == "exit")
        gui_condition = Gui_interface::Condition::exit;
    if (last_position == "beginning" && position == "class") {
        game_position->set_race(Position::player1, id);
    }
    if (last_position == "class" && position == "troops") {
        last_position = "none";
        game_position->set_class(Position::player1, id);
        auto& c_data = database.get_classes()[id];
        p_money[0] = c_data.start_money_A;
        p_money[1] = c_data.start_money_B;
        p_money[2] = c_data.start_money_C;
    }
    if (last_target_name == "back")
        game_position->reset(Position::Player::player1);
}