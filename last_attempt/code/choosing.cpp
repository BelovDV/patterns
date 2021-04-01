#include"choosing.h"

#include<fstream>

void read(std::vector<Unit::Data>& in)
{
	std::ifstream fin("data_unit");
	Unit::Data vsp;
	while (fin >> vsp)
		in.push_back(vsp);
	fin.close();
}

void Choosing::set_race(Gamer_types::Race race)
{
	player_choice.set_race(race);
	std::vector<Unit::Data> in;
	read(in);
	for (auto& iter : in)
		if (Gamer_types::get_race_from_string(iter.race) == race)
			available_units.push_back(iter);
}

void Choosing::choose_unit(int numer_in_available)
{
	chosen_units.push_back(available_units[numer_in_available]);
	player_money_A -= available_units[numer_in_available].info.cost_A;
	player_money_B -= available_units[numer_in_available].info.cost_B;
	player_money_C -= available_units[numer_in_available].info.cost_C;
}

void Choosing::modificate_unit(int number_in_chosen, Gamer_types::Ability_class ability)
{
	Gamer_types::modify(chosen_units[number_in_chosen].info, ability,
		Gamer_types::class_ability_list[player_choice.get_class()][ability].mode);
	player_money_M -= Gamer_types::class_ability_list[player_choice.get_class()][ability].cost;
}

void Choosing::set_class(Gamer_types::Class clas)
{
	player_choice.set_class(clas);
	for (auto& iter : available_units)
		for (int ability = 0; ability != Gamer_types::number_ability_class; ++ability)
			Gamer_types::modify(iter.info, Gamer_types::Ability_class(ability),	0);//TODO
}