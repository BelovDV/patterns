#include"../include/database.h"

#include<fstream>

std::ifstream& operator>>(std::ifstream& in, Data::Unit::Data& data)
{
	in
		>> data.id
		>> data.race
		>> data.name;
	for (int i = 0; i != Data::Constances::unit_number_info; ++i)
		in >> data.info.parameter[i];
	in >> data.info.skills;
	in
		>> data.cost_A
		>> data.cost_B
		>> data.cost_C;
	return in;
}

std::ifstream& operator>>(std::ifstream& in, Data::Class::Data& data)
{
	in
		>> data.id
		>> data.name
		>> data.skills;
	for (int i = 0; i != Data::Constances::unit_number_info; ++i)
		in
		>> data.start_active[i].type
		>> data.start_active[i].value
		>> data.start_active[i].cost;
	for (int i = 0; i != Data::Constances::unit_number_info; ++i)
		in
		>> data.start_passive[i].type
		>> data.start_passive[i].value;
	return in;
}

std::ifstream& operator>>(std::ifstream& in, Data::Race::Data& data)
{
	in
		>> data.id
		>> data.name;
	return in;
}

void Database::read()
{
	std::ifstream fin(Data::Constances::_file_name);
	std::string word, open, close;

	fin >> word;
	while (word[0] == '#')
		fin >> word;
	// Read races
	fin >> number_race >> open;
	races.resize(number_race);
	for (auto& it : races)
		fin >> it;
	fin >> close;
	// Read classes
	fin >> word >> number_class >> open;
	classes.resize(number_class);
	for (auto& it : classes)
		fin >> it;
	fin >> close;
	// Read units
	fin >> word >> number_units >> open;
	units.resize(number_units);
	for (auto& it : units)
		fin >> it;
	fin >> close;
	
	fin.close();

	for (auto& it : races)
		race_id[it.name] = it.id;
	for (auto& it : classes)
		class_id[it.name] = it.id;
	races_units.resize(number_race);
	for (auto& it : units)
		races_units[race_id[it.race]].push_back(it.id);
}

Database database;