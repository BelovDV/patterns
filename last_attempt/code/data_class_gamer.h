#pragma once

#include<vector>

#include"data_unit.h"

namespace Gamer_types
{
	using std::vector;

	static const int number_classes = 3;
	static const int number_races = 2;
	static const int number_ability_class = 6;

	enum Race
	{
		thirst,
		second
	};

	Race get_race_from_string(std::string race);

	enum Class
	{
		warrior,
		trader,
		magician
	};

	enum Ability_class
	{
		change_cost_A,
		change_cost_B,
		change_cost_C,
		change_dmin,
		change_dmax,
		change_xp
	};

	enum Ability_mode
	{
		add,
		multiply,
		set
	};

	struct Ability_using
	{
		Ability_using(bool p = false, Ability_mode m = Ability_mode::add, int v = 0, int c = 0) :
			possible(p), mode(m), value(v), cost(c) {}
		bool possible;
		Ability_mode mode;
		int value;
		int cost;
	};

	static vector<vector<Ability_using>> class_ability_list;
	void init_class_ability_list();

	static vector<vector<Ability_using>> class_passive_list;
	void init_class_passive_list();

	void modify(Unit::Info& info, Ability_class ability, Ability_using mode);
}