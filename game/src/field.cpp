#include "../include/field.h"

#include <vector>

Field::Field(int dd) : u_p(dd), u_n(-dd), d_p(dd), d_n(-dd)
{
    generate(Coordinate(0, 0), dd);
}

void Field::generate(Coordinate coord)
{
    field[coord] = Cell(Terrain::Grass, 0);
}

void Field::generate(Coordinate center, int dd)
{
    for (int u = -dd; u <= dd; ++u)
        for (int d = -dd; d <= dd; ++d)
            if (u - d <= dd && u - d >= -dd &&
            (field.find(Coordinate(center.u + u, center.d + d)) == field.end() ||
            field[Coordinate(center.u + u, center.d + d)].terrain == none))
                generate(Coordinate(center.u + u, center.d + d));
}

Field::Cell Field::get_cell(Coordinate coord)
{
    if (coord.u < u_n + 2 || coord.u > u_p - 2 || coord.d < d_n + 2 || coord.d > d_p - 2)
        generate(coord, 8);
    return field[coord];
}

Field::Cell Field::check_cell(Coordinate coord) const {
    if (field.find(coord) != field.end())
    {
        auto it = field.find(coord);
        return it->second;
    }
    return {};
}