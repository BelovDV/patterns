#pragma once

#include"field.h"

class Chooser
{
public:
	virtual Field_choice get_AI_choice(const Field& field) = 0;
};

class Choosing
{
	Field field;
	Field_choice player_choice;
	std::vector<Unit::Data> available_units;
	std::vector<Unit::Data> chosen_units;
	int player_money_A = 100;
	int player_money_B = 100;
	int player_money_C = 100;
	int player_money_M = 100;
	Chooser& AI;
public:
	Choosing(Chooser& AI) : AI(AI) {}
public:
	void set_race(Gamer_types::Race race);
	void set_class(Gamer_types::Class clas);
	std::vector<Unit::Data> get_units_list() { return available_units; }
	std::vector<Unit::Data> get_units_list_chosen() { return chosen_units; }
	void choose_unit(int numer_in_available);
	void modificate_unit(int number_in_chosen, Gamer_types::Ability_class ability);
	Field get_resulting_field() { field.set_gamer_2_choice(AI.get_AI_choice(field)); return field; }
	int get_money_A() { return player_money_A; }
	int get_money_B() { return player_money_B; }
	int get_money_C() { return player_money_C; }
	int get_money_M() { return player_money_M; }
};