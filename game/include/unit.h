#pragma once

#include "data.h"
#include "field.h"

#include <vector>

class Unit
{
public:
    Unit(int id, Field::Coordinate coord = Field::Coordinate());
public:
    int& operator[](Data::Unit::Parameter par);
    const int& operator[](Data::Unit::Parameter par) const;
    const std::string& get_name() const;
    void set_coordinates(Field::Coordinate);
    Field::Coordinate get_coordinates() const { return coord; }
    int get_time() const { return time_position; }
    void set_time(int time) { time_position = time; }
    bool operator<(const Unit& other) const;
    int get_id() const { return unit_id; }
private:
    static int counter;
    Data::Unit::Info info;
    int personal_id;
    int unit_id;
    int time_position = 0;
    Field::Coordinate coord;
};