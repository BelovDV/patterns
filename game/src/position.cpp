#include "position.h"
#include "log.h"
#include "database_loader.h"

namespace {
    const double base_distance = 100;
    const int base_start_delta_u = 5;
}

using Data::Unit::Parameter;

Position::Position() :
    ready(false),
    field(1)
{}

void Position::reset(Player player) {
    units[player].clear();
    units_storage[player].clear();
}

void Position::add_unit(Player player, const Unit& unit) {
    int sz = units_storage[player].size();
    units[player].insert({base_distance / unit[Parameter::initiative], sz});
    units_storage[player][sz] = unit;
}

#include <ctime>

void Position::start() {
    std::vector<std::vector<std::pair<double, int>>> vsp(2);
    for (int i = 0; i != 2; ++i)
        for (auto& it : units[i])
            vsp[i].emplace_back(it);
    units[0].clear();
    units[1].clear();

    srand(time(0));
    for (int p = 0; p != 2; ++p)
        for (auto& unit : vsp[p]) {
            int d = rand() % (int)(base_distance / 2);
            int init = units_storage[p][unit.second][Parameter::initiative];
            double base = (base_distance / 2 + d);
            unit.first = base / init;
        }
    for (int i = 0; i != 2; ++i)
        for (auto& unit : vsp[i])
            units[i].insert(unit);

    for (int i = 0; i != 2; ++i) {
        auto iter = units[i].begin();
        for (int j = 0; j != units[i].size(); ++j){
            units_storage[i][iter->second].set_coordinates(
                    base_start_delta_u * (2 * i - 1), j - units[i].size() / 2);
            field.get_cell(units_storage[i][iter->second].get_coordinates());
            set_coordinates[i].insert(units_storage[i][iter->second].get_coordinates());
            ++iter;
        }
    }

    ready = true;
}

void Position::set_race(Position::Player player, int id) {
    if (ready)
        return;
    race_id[player] = id;
}

void Position::set_class(Position::Player player, int id) {
    if (ready)
        return;
    class_id[player] = id;
}

int Position::get_race(Position::Player player) const {
    return race_id[player];
}

int Position::get_class(Position::Player player) const {
    return class_id[player];
}

bool Position::end() const {
    return units[0].empty() || units[1].empty();
}

const Unit& Position::get_next_unit() const {
    if (units[0].begin()->first < units[1].begin()->first)
        return units_storage[0].find(units[0].begin()->second)->second;
    return units_storage[1].find(units[1].begin()->second)->second;
}

Position::Player Position::get_next_player() const {
    if (units[0].begin()->first < units[1].begin()->first)
        return player1;
    return player2;
}

void Position::move(Field::Coordinate coord) {
    if (end())
        return;

    field.get_cell(coord);

    auto player = get_next_player();
    std::vector<std::vector<std::pair<double, int>>> vsp(2);
    for (int i = 0; i != 2; ++i)
        for (auto& it : units[i])
            vsp[i].emplace_back(it);
    units[0].clear();
    units[1].clear();

    set_coordinates[player].erase(
            units_storage[player][vsp[player][0].second].get_coordinates());
    units_storage[player][vsp[player][0].second].set_coordinates(coord);
    set_coordinates[player].insert(coord);
    double dt = vsp[player][0].first;
    for (auto& u_p : vsp)
        for (auto& unit : u_p)
            unit.first -= dt;
    vsp[player][0].first = (base_distance / 2 + (base_distance / 2) / (rand() + 1)) /
            units_storage[player][vsp[player][0].second][Parameter::initiative];

    for (int i = 0; i != 2; ++i)
        for (auto& unit : vsp[i])
            units[i].insert(unit);
}

std::map<int, int> Position::get_count_list_units(Player player) const {
    std::map<int, int> ans;
    for (auto& unit : units[player])
        ans[units_storage[player].find(unit.second)->second.get_id()] += 1;
    return ans;
}

void Position::attack_unit(Field::Coordinate coord, const Unit &attacker) {
    for (int p = 0; p != 2; ++p)
        for (auto& unit : units_storage[p])
            if (coord == unit.second.get_coordinates())
            {
                int damage = attacker[Data::Unit::Parameter::damage_max];
                unit.second[Data::Unit::Parameter::hp] -= damage;
                if (unit.second[Data::Unit::Parameter::hp] <= 0)
                {
                    for (auto iter = units[p].begin(); iter != units[p].end(); ++iter)
                        if (iter->second == unit.first)
                        {
                            units[p].erase(iter);
                            break;
                        }
                    set_coordinates[p].erase(coord);
                    units_storage[p].erase(unit.first);
                    return;
                }
            }
}