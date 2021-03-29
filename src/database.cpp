#include"../include/database.h"

#include<fstream>

void Database::read()
{
	std::ifstream fin(Data::Constances::_file_name);
	std::string word, open, close;

	fin >> word;
	while (word[0] == '#')
		fin >> word;

	// Read races
	fin >> number_race >> open;
	if (word != "races")
		errors.push_back("Read: Didn't find races");
	if (open != "{")
		errors.push_back("Read: Didn't find '{' with races");
	if (number_race < 0 || number_race > 1000)
		errors.push_back("Read: Strange value number of races");
	races.resize(number_race);
	for (auto& it : races)
	{
		fin >> it;
		race_id[it.name] = it.id;
	}
	fin >> close;
	if (close != "};")
		errors.push_back("Read: Didn't find '};' with races");

	// Read classes
	fin >> word >> number_class >> open;
	if (word != "classes")
		errors.push_back("Read: Didn't find classes");
	if (open != "{")
		errors.push_back("Read: Didn't find '{' with classes");
	if (number_class < 0 || number_class > 1000)
		errors.push_back("Read: Strange value number of classes");
	classes.resize(number_class);
	for (auto& it : classes)
	{
		fin >> it;
		class_id[it.name] = it.id;
	}
	fin >> close;
	if (close != "};")
		errors.push_back("Read: Didn't find '};' with classes");

	// Read units
	fin >> word >> number_units >> open;
	if (word != "units")
		errors.push_back("Read: Didn't find units");
	if (open != "{")
		errors.push_back("Read: Didn't find '{' with units");
	if (number_units < 0 || number_units > 100000)
		errors.push_back("Read: Strange value number of units");
	units.resize(number_race);
	for (int i = 0; i != number_units; ++i)
	{
		Data::Unit::Data vsp;
		fin >> vsp;
		if (race_id.find(vsp.race) != race_id.end())
			units[race_id[vsp.race]].push_back(vsp);
		else
			errors.push_back("Read:unit: race doesn't exists");
	}
	fin >> close;
	if (close != "};")
		errors.push_back("Read: Didn't find '};' with units");

	fin.close();
}