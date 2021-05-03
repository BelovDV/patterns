#include"database.h"

void Database::initialise()
{
	for (auto& it : races)
		race_id[it.name] = it.id;
	for (auto& it : classes)
		class_id[it.name] = it.id;
	races_units.resize(number_race);
	for (auto& it : units)
		races_units[race_id[it.race]].push_back(it.id);
}