#include "data_class_gamer.h"

using namespace Gamer_types;

Race Gamer_types::get_race_from_string(std::string race)
{
	if (race == "race_1")
		return Race::thirst;
	else
		return Race::second;
}

void Gamer_types::init_class_ability_list()
{
	auto& cal = class_ability_list;
	cal.resize(number_classes);
	for (auto& it : cal)
		it.resize(number_ability_class);

	cal[Class::magician][Ability_class::change_cost_A] = Ability_using(false);
	cal[Class::magician][Ability_class::change_cost_B] = Ability_using(false);
	cal[Class::magician][Ability_class::change_cost_C] = Ability_using(true, Ability_mode::set, 0, 0);
	cal[Class::magician][Ability_class::change_dmax] = Ability_using(false);
	cal[Class::magician][Ability_class::change_dmin] = Ability_using(false);
	cal[Class::magician][Ability_class::change_xp] = Ability_using(false);

	cal[Class::warrior][Ability_class::change_cost_A] = Ability_using(false);
	cal[Class::warrior][Ability_class::change_cost_B] = Ability_using(false);
	cal[Class::warrior][Ability_class::change_cost_C] = Ability_using(false);
	cal[Class::warrior][Ability_class::change_dmax] = Ability_using(true, Ability_mode::add, 1, 10);
	cal[Class::warrior][Ability_class::change_dmin] = Ability_using(true, Ability_mode::add, 1, 10);
	cal[Class::warrior][Ability_class::change_xp] = Ability_using(true, Ability_mode::add, 10, 10);

	cal[Class::trader][Ability_class::change_cost_A] = Ability_using(true, Ability_mode::add, -1, 10);
	cal[Class::trader][Ability_class::change_cost_B] = Ability_using(true, Ability_mode::add, -1, 10);
	cal[Class::trader][Ability_class::change_cost_C] = Ability_using(false);
	cal[Class::trader][Ability_class::change_dmax] = Ability_using(false);
	cal[Class::trader][Ability_class::change_dmin] = Ability_using(false);
	cal[Class::trader][Ability_class::change_xp] = Ability_using(false);
}

void Gamer_types::init_class_passive_list()
{
	auto& cal = class_passive_list;
	cal.resize(number_classes);
	for (auto& it : cal)
	it.resize(number_ability_class);

	cal[Class::magician][Ability_class::change_cost_A] = Ability_using(false);
	cal[Class::magician][Ability_class::change_cost_B] = Ability_using(false);
	cal[Class::magician][Ability_class::change_cost_C] = Ability_using(false);
	cal[Class::magician][Ability_class::change_dmax] = Ability_using(false);
	cal[Class::magician][Ability_class::change_dmin] = Ability_using(false);
	cal[Class::magician][Ability_class::change_xp] = Ability_using(true, Ability_mode::add, 1, 0);

	cal[Class::warrior][Ability_class::change_cost_A] = Ability_using(false);
	cal[Class::warrior][Ability_class::change_cost_B] = Ability_using(false);
	cal[Class::warrior][Ability_class::change_cost_C] = Ability_using(false);
	cal[Class::warrior][Ability_class::change_dmax] = Ability_using(true, Ability_mode::add, 1, 0);
	cal[Class::warrior][Ability_class::change_dmin] = Ability_using(true, Ability_mode::add, 1, 0);
	cal[Class::warrior][Ability_class::change_xp] = Ability_using(false);

	cal[Class::trader][Ability_class::change_cost_A] = Ability_using(true, Ability_mode::add, -1, 0);
	cal[Class::trader][Ability_class::change_cost_B] = Ability_using(true, Ability_mode::add, -1, 0);
	cal[Class::trader][Ability_class::change_cost_C] = Ability_using(false);
	cal[Class::trader][Ability_class::change_dmax] = Ability_using(false);
	cal[Class::trader][Ability_class::change_dmin] = Ability_using(false);
	cal[Class::trader][Ability_class::change_xp] = Ability_using(false);
}

void Gamer_types::modify(Unit::Info& info, Ability_class ability, Ability_using mode)
{
	if (!mode.possible)
		return;
	int Unit::Info::* position;
	if (ability == Ability_class::change_cost_A)
		position = &Unit::Info::cost_A;
	else if (ability == Ability_class::change_cost_B)
		position = &Unit::Info::cost_B;
	else if (ability == Ability_class::change_cost_C)
		position = &Unit::Info::cost_A;
	else if (ability == Ability_class::change_dmax)
		position = &Unit::Info::damage_max;
	else if (ability == Ability_class::change_dmin)
		position = &Unit::Info::damage_min;
	else if (ability == Ability_class::change_xp)
		position = &Unit::Info::hp;
	
	if (mode.mode == Ability_mode::add)
		info.*position += mode.value;
	else if (mode.mode == Ability_mode::multiply)
		info.*position *= mode.value;
	else if (mode.mode == Ability_mode::set)
		info.*position = mode.value;
}