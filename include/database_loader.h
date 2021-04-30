#pragma once

#include "database.h"

#include <fstream>

class Database_loader : public Database
{
public:
	void load(const std::string& file);
private:
	void load_unit(std::ifstream& in, Data::Unit::Data& data);
	void load_race(std::ifstream& in, Data::Race::Data& data);
	void load_class(std::ifstream& in, Data::Class::Data& data);
};