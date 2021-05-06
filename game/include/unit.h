#pragma once

#include "data.h"
#include "field.h"

#include <vector>

class Unit
{
public:
    explicit Unit(int id, Field::Coordinate coord = Field::Coordinate());
    Unit() : Unit(0) {}
public:
    int& operator[](Data::Unit::Parameter par);
    const int& operator[](Data::Unit::Parameter par) const;
    const std::string& get_name() const;
    void set_coordinates(Field::Coordinate);
    void set_coordinates(int u, int d) {set_coordinates(Field::Coordinate(u, d));}
    Field::Coordinate get_coordinates() const { return coord; }
    bool operator<(const Unit& other) const;
    int get_id() const { return unit_id; }
private:
    static int counter;
    Data::Unit::Info info;
    int personal_id;
    int unit_id;
    Field::Coordinate coord;
};