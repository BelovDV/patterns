#pragma once

#include "field.h"
#include "unit.h"

#include <vector>
#include <set>

class Position
{
public:
    enum Player
    {
        first,
        second
    };
public:
    Position();
public:
    void add_unit(Player player, Unit&& unit);
    void initialise();
public:
    void set_race(Player, int id);
    void set_class(Player, int id);
    int get_race(Player);
    int get_class(Player);
    void reset(Player player) { units[player].clear(); }
    std::vector<std::pair<int, int>> get_list_units(Player); // id-count
private:
    Field field;
    std::vector<std::set<Unit>> units;
    std::vector<int> race_id = std::vector<int>(2, -1);
    std::vector<int> class_id = std::vector<int>(2, -1);
};