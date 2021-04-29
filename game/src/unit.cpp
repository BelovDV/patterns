#include "../include/unit.h"

#include "database_loader.h"

Unit::Unit(int id, Field::Coordinate coord) :
    personal_id(++counter),
    unit_id(id),
    info(database.get_units()[id].info),
    coord(coord)
{}

int& Unit::operator[](Data::Unit::Parameter par) {
    return info.parameter[par];
}

const int& Unit::operator[](Data::Unit::Parameter par) const {
    return info.parameter[par];
}

const std::string& Unit::get_name() const {
    return database.get_units()[unit_id].name;
}

void Unit::set_coordinates(Field::Coordinate coordinate) {
    coord = coordinate;
}

bool Unit::operator<(const Unit &other) const {
    if (time_position != other.time_position)
        return time_position < other.time_position;
    return personal_id < other.personal_id;
}

int Unit::counter = 0;