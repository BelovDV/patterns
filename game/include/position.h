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
        player1,
        player2
    };
public:
    Position();
public:
    void add_unit(Player player, const Unit& unit);
    void set_race(Player, int id);
    void set_class(Player, int id);
    int get_race(Player) const;
    int get_class(Player) const;
    void reset(Player player);
    void start();
public:
    const Field& get_field() const {return field;}
    const Unit& get_next_unit() const;
    Player get_next_player() const;
    void move(Field::Coordinate);
    const std::set<Field::Coordinate>& get_coordinates(Player p) const {return set_coordinates[p];}
    const std::map<int, Unit>& get_units(Player p) const {return units_storage[p];}
    std::map<int, int> get_count_list_units(Player player) const;
    void attack_unit(Field::Coordinate coord, const Unit& attacker);
    bool end() const;
private:
    bool ready;
    Field field;
    std::vector<int> race_id = std::vector<int>(2, -1);
    std::vector<int> class_id = std::vector<int>(2, -1);
    std::vector<std::map<int, Unit>> units_storage =
            std::vector<std::map<int, Unit>>(2);
    std::vector<std::multimap<double, int>> units =
            std::vector<std::multimap<double, int>>(2);
    std::vector<std::set<Field::Coordinate>> set_coordinates =
            std::vector<std::set<Field::Coordinate>>(2);
};