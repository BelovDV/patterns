#include "position.h"
#include "log.h"
#include "database_loader.h"

Position::Position() :
    field(10),
    units(std::vector<std::set<Unit>>(2))
{}

void Position::add_unit(Player player, Unit &&unit) {
    units[player].insert(unit);
}

void Position::initialise() {
    srand(1);
    for (int i = units[0].size() + units[1].size(); i >= 0; --i)
    {
        // todo - change unit's time position
    }
}

void Position::set_race(Position::Player player, int id) {
    race_id[player] = id;
}

void Position::set_class(Position::Player player, int id) {
    class_id[player] = id;
}

int Position::get_race(Position::Player player) {
    return race_id[player];
}

int Position::get_class(Position::Player player) {
    return class_id[player];
}

std::vector<std::pair<int, int>> Position::get_list_units(Position::Player player) {
    std::vector<std::pair<int, int>> ans;
    for (auto& it : database.get_races_units()[race_id[player]])
        ans.emplace_back(it, 0);
    for (const auto& it : units[player])
        for (auto& pos : ans)
            if (pos.first == it.get_id())
                pos.second += 1;
    return ans;
}