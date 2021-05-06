#include "database_loader.h"

#include<fstream>

void Database_loader::load_unit(std::ifstream& in, Data::Unit::Data& data)
{
	in >> data.id >> data.race >> data.name;
	for (int i = 0; i != Data::Constants::unit_number_info; ++i)
		in >> data.info.parameter[i];
	in >> data.info.skills >> data.cost_A >> data.cost_B >> data.cost_C >> data.image_id;
}

void Database_loader::load_class(std::ifstream& in, Data::Class::Data& data)
{
	in >> data.id >> data.name >> data.skills >>
	    data.start_money_A >> data.start_money_B >> data.start_money_C;
	for (int i = 0; i != Data::Constants::unit_number_info; ++i)
		in >> data.start_active[i].type >> data.start_active[i].value >> data.start_active[i].cost;
	for (int i = 0; i != Data::Constants::unit_number_info; ++i)
		in >> data.start_passive[i].type >> data.start_passive[i].value;
}

void Database_loader::load_race(std::ifstream& in, Data::Race::Data& data)
{
	in >> data.id >> data.name;
}

void Database_loader::load(const std::string& file)
{
	std::ifstream fin(file);
	std::string buffer;

	fin >> buffer;
	while (buffer[0] == '#')
		fin >> buffer;
	fin >> number_race >> buffer;
	races.resize(number_race);
	for (auto& it : races) load_race(fin, it);
	fin >> buffer >> buffer >> number_class >> buffer;
	classes.resize(number_class);
	for (auto& it : classes) load_class(fin, it);
	fin >> buffer >> buffer >> number_units >> buffer;
	units.resize(number_units);
	for (auto& it : units) load_unit(fin, it);
	fin >> buffer;
}