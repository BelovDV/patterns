#include "game_fight.h"

Game_fight::Game_fight(Position* start_position) :
    position(start_position)
{
    generate_possible_ways();
    generate_possible_attack();
}

void Game_fight::generate_possible_ways() {
    if (position->end())
        return;

    auto player = position->get_next_player();
    auto unit = position->get_next_unit();

    possible_ways.assign(1, unit.get_coordinates());
    std::set<Field::Coordinate> vsp;
    for (int i = 0; i != unit[Data::Unit::speed]; ++i)
    {
        for (auto& cell : possible_ways)
            for (auto n : cell.neighbours())
                if (position->get_coordinates(Position::player1).find(n) ==
                    position->get_coordinates(Position::player1).end() &&
                    position->get_coordinates(Position::player2).find(n) ==
                    position->get_coordinates(Position::player2).end() &&
                    n.u < 50 && n.u > -50 && n.d < 50 && n.d > -50)
                    vsp.insert(n);
        possible_ways.clear();
        for (auto& cell : vsp)
            possible_ways.push_back(cell);
    }
    possible_ways.push_back(unit.get_coordinates());
}

void Game_fight::generate_possible_attack() {
    possible_attack.clear();
    std::set<Field::Coordinate> possible;
    auto& unit = position->get_next_unit();
    auto range = unit[Data::Unit::Parameter::shooter];
    for (auto& coord : possible_ways)
    {
        possible.insert(coord);
        for (int u = -range; u <= range; ++u)
            for (int d = -range; d <= range; ++d)
                if (u - d <= range && d - u <= range)
                    possible.insert(Field::Coordinate(coord.u + u, coord.d + d));
    }
    auto foe = Position::Player(1 - position->get_next_player());
    for (auto& coord : possible)
        if (position->get_coordinates(foe).find(coord) != position->get_coordinates(foe).end())
            possible_attack.push_back(coord);
}

void Game_fight::press(Field::Coordinate coord) {
    for (auto& it : possible_ways)
        if (it == coord)
        {
            position->move(coord);
            generate_possible_ways();
            generate_possible_attack();
            return;
        }
    for (auto& it : possible_attack)
        if (it == coord)
        {
            for (auto& place : get_possible_ways())
            {
                std::set<Field::Coordinate> possible;
                auto range = position->get_next_unit()[Data::Unit::Parameter::shooter];
                for (int u = -range; u <= range; ++u)
                    for (int d = -range; d <= range; ++d)
                        if (u - d <= range && d - u <= range)
                            possible.insert(Field::Coordinate(place.u + u, place.d + d));
                if (possible.find(coord) != possible.end())
                {
                    position->attack_unit(coord, position->get_next_unit());
                    press(place);
                    return;
                }
            }
        }
}

Field::Coordinate Game_fight::get_next_coordinate() const {
    return position->get_next_unit().get_coordinates();
}