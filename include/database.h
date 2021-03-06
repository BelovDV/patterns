#pragma once

#include"data.h"

#include <unordered_map>
#include <vector>

// ===== // ===== // ===== // ===== // ===== //

class Database
{
public:
	Database() {}
public:
	void initialise();
	const std::vector<Data::Race::Data>& get_races() const { return races; }
	const std::vector<Data::Class::Data>& get_classes() { return classes; }
	const std::vector<Data::Unit::Data>& get_units() { return units; }
	const std::unordered_map<std::string, int>& get_race_id() { return race_id; }
	const std::unordered_map<std::string, int>& get_class_id() { return class_id; }
	const std::vector<std::vector<int>>& get_races_units() { return races_units; }
protected:
	int number_race = -1;
	int number_class = -1;
	int number_units = -1;
	std::vector<Data::Race::Data> races;
	std::vector<Data::Class::Data> classes;
	std::vector<Data::Unit::Data> units;
	std::unordered_map<std::string, int> race_id;
	std::unordered_map<std::string, int> class_id;
	std::vector<std::vector<int>> races_units;
};

// ===== // ===== // ===== // ===== // ===== //