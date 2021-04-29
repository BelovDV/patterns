#pragma once

#include<string>
#include<bitset>
#include <vector>

namespace Data
{
	struct Constants
	{
		static const int unit_number_info = 10;
		static const int unit_number_skills = 2;
		static const int class_number_skills = 2;
		static const std::vector<std::string> unit_parameters;
	};

	namespace Race
	{
		struct Data
		{
			int id;
			std::string name;
		};
	}

	namespace Class
	{
		enum Skill
		{
			none1,
			none2
		};

		struct Transform_passive
		{
			int type;
			int value;
		};

		struct Transform_active
		{
			int type;
			int value;
			int cost;
		};

		struct Data
		{
			Transform_active start_active[Constants::unit_number_info];
			Transform_passive start_passive[Constants::unit_number_info];
			std::bitset<Constants::class_number_skills> skills;
			int id;
			std::string name;
			int start_money_A, start_money_B, start_money_C;
		};
	}

	namespace Unit
	{
		enum Parameter
		{
			lvl,
			attack,
			defense,

			damage_min,
			damage_max,
			hp,

			speed,
			initiative,

			shooter,
			magician,
		};

		enum Skill
		{
			none1,
			none2
		};

		struct Info
		{
			int parameter[Constants::unit_number_info];
			std::bitset<Constants::unit_number_skills> skills;
		};

		struct Data
		{
			int id;
			int cost_A;
			int cost_B;
			int cost_C;
			Info info;
			std::string race;
			std::string name;
		};
	}
}