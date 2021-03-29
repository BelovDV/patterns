#pragma once

#include<string>
#include<bitset>

namespace Data
{
	struct Constances
	{
		const static std::string _file_name;

		static const int _unit_number_info = 10;
		static const int _unit_number_skills = 2;
		static const int _class_number_skills = 2;
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
			Transform_active start_active[Constances::_unit_number_info];
			Transform_passive start_passive[Constances::_unit_number_info];
			std::bitset<Constances::_class_number_skills> skills;
			int id;
			std::string name;
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
			int parameter[Constances::_unit_number_info];
			std::bitset<Constances::_unit_number_skills> skills;
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

template<typename Stream>
Stream& operator>>(Stream& in, Data::Unit::Info& info)
{
	for (int i = 0; i != Data::Constances::_unit_number_info; ++i)
		in >> info.parameter[i];
	in >> info.skills;
	return in;
}

template<typename Stream>
Stream& operator>>(Stream& in, Data::Unit::Data& data)
{
	in
		>> data.id
		>> data.race
		>> data.name
		>> data.info
		>> data.cost_A
		>> data.cost_B
		>> data.cost_C;
	return in;
}

template<typename Stream>
Stream& operator>>(Stream& in, Data::Class::Transform_active& data)
{
	in
		>> data.type
		>> data.value
		>> data.cost;
	return in;
}

template<typename Stream>
Stream& operator>>(Stream& in, Data::Class::Transform_passive& data)
{
	in
		>> data.type
		>> data.value;
	return in;
}

template<typename Stream>
Stream& operator>>(Stream& in, Data::Class::Data& data)
{
	in
		>> data.id
		>> data.name
		>> data.skills;
	for (int i = 0; i != Data::Constances::_unit_number_info; ++i)
		in >> data.start_active[i];
	for (int i = 0; i != Data::Constances::_unit_number_info; ++i)
		in >> data.start_passive[i];
	return in;
}

template<typename Stream>
Stream& operator>>(Stream& in, Data::Race::Data& data)
{
	in
		>> data.id
		>> data.name;
	return in;
}

template<typename Stream>
Stream& operator<<(Stream& out, const Data::Unit::Info& info)
{
	for (int i = 0; i != Data::Constances::_unit_number_info; ++i)
		out << info.parameter[i] << ' ';
	out << info.skills;
	return out;
}

template<typename Stream>
Stream& operator<<(Stream& out, const Data::Unit::Data& data)
{
	out
		<< data.id << '\t'
		<< data.race << '\t'
		<< data.name << '\t'
		<< data.info << '\t'
		<< data.cost_A << ' '
		<< data.cost_B << ' '
		<< data.cost_C;
	return out;
}

template<typename Stream>
Stream& operator<<(Stream& out, const Data::Class::Transform_active& data)
{
	out
		<< data.type << ' '
		<< data.value << ' '
		<< data.cost;
	return out;
}

template<typename Stream>
Stream& operator<<(Stream& out, const Data::Class::Transform_passive& data)
{
	out
		<< data.type << ' '
		<< data.value;
	return out;
}

template<typename Stream>
Stream& operator<<(Stream& out, const Data::Class::Data& data)
{
	out
		<< data.id << '\t'
		<< data.name << '\t'
		<< data.skills << '\t';
	for (int i = 0; i != Data::Constances::_unit_number_info; ++i)
		out << data.start_active[i] << ' ';
	for (int i = 0; i != Data::Constances::_unit_number_info; ++i)
		out << data.start_passive[i] << ' ';
	return out;
}

template<typename Stream>
Stream& operator<<(Stream& out, const Data::Race::Data& data)
{
	out
		<< data.id << '\t'
		<< data.name;
	return out;
}