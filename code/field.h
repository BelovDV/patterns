#pragma once

#include<map>
#include<vector>

#include"data_unit.h"
#include"data_class_gamer.h"

struct Coord
{
	int a;
	int b;
};

bool operator<(const Coord& a, const Coord& b);

struct Soil
{
	int hardness = 1;
};

struct Hex
{
	int id_unit;
	Unit::Info unit;
	Soil soil;
};

struct Location_unit
{
	Coord coord;
	int id;
	Unit::Info unit;
};

class Field_choice
{
	std::vector<Location_unit> units;
	Gamer_types::Race race;
	Gamer_types::Class clas;
public:
	Field_choice() {}
	Field_choice(const std::vector<Location_unit>& u) : units(u) {}
public:
	void set_units(const std::vector<Location_unit>& u) { units = u; }
	const std::vector<Location_unit>& get() const { return units; }
	void set_race(Gamer_types::Race r) { race = r; }
	void set_class(Gamer_types::Class c) { clas = c; }
	Gamer_types::Class get_class() { return clas; }
};

class Field
{
	std::map<Coord, Hex> map;
	std::vector<Location_unit> units_1;
	std::vector<Location_unit> units_2;
	Field_choice choice_1;
	Field_choice choice_2;
public:
	Field() {}
public:
	void generate_map() {}
	const std::map<Coord, Hex>& get_map() const { return map; }
	void set_gamer_1_choice(Field_choice choice) { choice_1 = choice; }
	void set_gamer_2_choice(Field_choice choice) { choice_1 = choice; }
};