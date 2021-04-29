#pragma once

#include "database.h"

#include <fstream>

class Database_loader : public Database
{
public:
	void load(const std::string& file);
private:
	static void load_unit(std::ifstream& in, Data::Unit::Data& data);
	static void load_race(std::ifstream& in, Data::Race::Data& data);
	static void load_class(std::ifstream& in, Data::Class::Data& data);
};

extern Database_loader database;