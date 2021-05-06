#pragma once

#include "position.h"

class Game_fight {
public:
    explicit Game_fight(Position* start_position);
public:
    const Position* get_position() const {return position;}
    std::vector<Field::Coordinate> get_possible_ways() const {return possible_ways;}
    std::vector<Field::Coordinate> get_possible_attack() const {return possible_attack;}
    void generate_possible_ways();
    void generate_possible_attack();
    Field::Coordinate get_next_coordinate() const;
    const Unit& get_next_unit() const {return position->get_next_unit();}
    //std::pair<Position::Player, int> get_player_unit_id(Field::Coordinate coord) const;
    void press(Field::Coordinate coord);
    //bool check_foe(Field::Coordinate coord, Position::Player player) const;
    //bool check_ally(Field::Coordinate coord, Position::Player player) const;
    //void move(Field::Coordinate coord);
    //void attack(Field::Coordinate coord);
    //void end();
private:
    Position* position;
    std::vector<Field::Coordinate> possible_ways;
    std::vector<Field::Coordinate> possible_attack;
};