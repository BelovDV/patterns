#pragma once

#include "gui_objects.h"
#include "position.h"
#include "window_interface.h"

class Game_drawer_field
{
public:
    enum Images
    {
        grass,
        transparent,
        red_shield,
        red_trans,
        red_0,
        red_1,
        red_2,
        red_3,
        red_4,
        red_5,
        blue_shield,
        blue_trans,
        blue_0,
        blue_1,
        blue_2,
        blue_3,
        blue_4,
        blue_5,
        hex_red,
        hex_green,
        count
    };
public:
    explicit Game_drawer_field(gi::Vector center);
public:
    void draw(Images, Field::Coordinate, Window_interface* window);
    void change_coordinate(gi::Vector change);
    bool contain_strict(Field::Coordinate) const;
    bool contain(Field::Coordinate) const;
    Field::Coordinate get_coord(gi::Vector mouse_coord) const;
private:
    std::vector<gi::Texture*> textures;
    std::vector<gi::Sprite*> sprites;
    gi::Vector view_coordinate;
    gi::Vector screen_size;
};