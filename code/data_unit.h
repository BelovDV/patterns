#pragma once

#include<string>

namespace Unit
{
	struct Info
	{
		static std::string description;
		int lvl;
		int attack;
		int defense;
		int damage_min;
		int damage_max;
		int hp;
		int speed;
		int initiative;
		int cost_A;
		int cost_B;
		int cost_C;
		int being_id;
	};

	struct Data
	{
		static std::string description;
		int id;
		Info info;
		std::string race;
		std::string name;
	};

	
	// is it good to use static var (waste static memory)?
}

template<typename Stream>
Stream& operator>>(Stream& in, Unit::Info& info)
{
	in >> info.lvl >> info.attack >> info.defense >> info.damage_min >>
		info.damage_max >> info.hp >> info.speed >> info.initiative >>
		info.being_id >> info.cost_A >> info.cost_B >> info.cost_C;
	return in;
}

template<typename Stream>
Stream& operator>>(Stream& in, Unit::Data& data)
{
	in >> data.id >> data.race >> data.name >> data.info;
	return in;
}

template<typename Stream>
Stream& operator<<(Stream& out, const Unit::Info& info)
{
	out << info.lvl << '\t' 
		<< info.attack << ' ' 
		<< info.defense << '\t'
		<< info.damage_min << ' '
		<< info.damage_max << '\t'
		<< info.hp << '\t'
		<< info.speed << '\t'
		<< info.initiative << '\t'
		<< info.being_id << '\t'
		<< info.cost_A << ' '
		<< info.cost_B << ' '
		<< info.cost_C << ' ';
	return out;
}

template<typename Stream>
Stream& operator<<(Stream& out, const Unit::Data& data)
{
	out << data.id << '\t'
		<< data.race << '\t'
		<< data.name << '\t'
		<< data.info << '\t';
	return out;
}