#pragma once

#include <map>

class Field
{
public:
    struct Coordinate
    {
        // hexagonal grid, u - right-up, d - right-down
        explicit Coordinate(int u = 0, int d = 0) : u(u), d(d) {}
        int u;
        int d;
        bool operator<(const Coordinate& other) const
        {
            return u < other.u || u == other.u && d < other.d;
        }
    };
    enum Terrain
    {
        none,
        Grass,
        Water,
        Road,
        Rock
    };
    struct Cell
    {
        Cell(Terrain ter = Terrain::none, int h = 0) : terrain(ter), h(h) {}
        Terrain terrain;
        int h;
    };
public:
    Field(int dd);
public:
    void generate(Coordinate coord);
    void generate(Coordinate center, int dd);
    Cell get_cell(Coordinate coord);
private:
    std::map<Coordinate, Cell> field;
    int u_p, u_n, d_p, d_n; // u positive...
};