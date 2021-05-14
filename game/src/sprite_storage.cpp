#include "sprite_storage.h"

namespace
{
    const int base_size_x = 1920;
    const int base_size_y = 1080;
    const int texture_size = 50;
    const int field_frame_simple = 100;
    const int field_frame_strict = 150;
}

Game_drawer_field::Game_drawer_field(gi::Vector center) :
        screen_size(center),
        view_coordinate(center.x / 2, center.y / 2)
{
    for (int i = 0; i != count; ++i)
        textures.push_back(gi::Texture::generate());
    textures[grass]->load("../data/image/grass.png");
    textures[transparent]->load("../data/image/hex_transparent.png");
    textures[hex_red]->load("../data/image/hex_transparent_red.png");
    textures[hex_green]->load("../data/image/hex_transparent_green.png");

    textures[red_shield]->load("../data/image/red_shield.png");
    textures[red_trans]->load("../data/image/red_shield_transparent.png");
    textures[red_0]->load("../data/image/red_0.png");
    textures[red_1]->load("../data/image/red_1.png");
    textures[red_2]->load("../data/image/red_2.png");
    textures[red_3]->load("../data/image/red_3.png");
    textures[red_4]->load("../data/image/red_4.png");
    textures[red_5]->load("../data/image/red_5.png");

    textures[blue_shield]->load("../data/image/blue_shield.png");
    textures[blue_trans]->load("../data/image/blue_shield_transparent.png");
    textures[blue_0]->load("../data/image/blue_0.png");
    textures[blue_1]->load("../data/image/blue_1.png");
    textures[blue_2]->load("../data/image/blue_2.png");
    textures[blue_3]->load("../data/image/blue_3.png");
    textures[blue_4]->load("../data/image/blue_4.png");
    textures[blue_5]->load("../data/image/blue_5.png");

    for (int i = 0; i != count; ++i) {
        sprites.push_back(gi::Sprite::generate());
        sprites[i]->set_texture(*textures[i]);
    }
}

void Game_drawer_field::draw(Images image, Field::Coordinate coord, Window_interface *window) {
    if (contain_strict(coord)) {
        sprites[image]->set_position(
                gi::Vector(coord.u * 25 + coord.d * 25 + view_coordinate.x - 100,
                           coord.u * 35 - coord.d * 35 + view_coordinate.y - 50));
        sprites[image]->draw(*window);
    }
    else if (contain(coord) && image == grass){
        sprites[transparent]->set_position(
                gi::Vector(coord.u * 25 + coord.d * 25 + view_coordinate.x - 100,
                           coord.u * 35 - coord.d * 35 + view_coordinate.y - 50));
        sprites[transparent]->draw(*window);
    }
    else if (contain(coord) && (image == red_shield || (image >= red_0 && image <= red_5))){
        sprites[red_trans]->set_position(
                gi::Vector(coord.u * 25 + coord.d * 25 + view_coordinate.x - 100,
                           coord.u * 35 - coord.d * 35 + view_coordinate.y - 50));
        sprites[red_trans]->draw(*window);
    }
    else if (contain(coord) && (image == blue_shield || (image >= blue_0 && image <= blue_5))){
        sprites[blue_trans]->set_position(
                gi::Vector(coord.u * 25 + coord.d * 25 + view_coordinate.x - 100,
                           coord.u * 35 - coord.d * 35 + view_coordinate.y - 50));
        sprites[blue_trans]->draw(*window);
    }
}

void Game_drawer_field::change_coordinate(gi::Vector change) {
    view_coordinate.x += change.x;
    view_coordinate.y += change.y;
}

bool Game_drawer_field::contain(Field::Coordinate coord) const {
    return
            view_coordinate.x + coord.u * 25 + coord.d * 25 > field_frame_simple + 50 &&
            view_coordinate.x + coord.u * 25 + coord.d * 25 < screen_size.x - field_frame_simple &&
            view_coordinate.y + coord.u * 35 - coord.d * 35 > field_frame_simple &&
            view_coordinate.y + coord.u * 35 - coord.d * 35 < screen_size.y - field_frame_simple;

}

bool Game_drawer_field::contain_strict(Field::Coordinate coord) const {
    return
            view_coordinate.x + coord.u * 25 + coord.d * 25 > field_frame_strict + 50 &&
            view_coordinate.x + coord.u * 25 + coord.d * 25 < screen_size.x - field_frame_strict &&
            view_coordinate.y + coord.u * 35 - coord.d * 35 > field_frame_strict &&
            view_coordinate.y + coord.u * 35 - coord.d * 35 < screen_size.y - field_frame_strict;
}

Field::Coordinate Game_drawer_field::get_coord(gi::Vector mouse_coord) const {
    for (int u = -200; u != 200; ++u) // field never will be such size
        for (int d = -200; d != 200; ++d)
        {
            gi::Vector check(u * 25 + d * 25 + view_coordinate.x - 100,
                       u * 35 - d * 35 + view_coordinate.y - 50);
            if ((check.x - mouse_coord.x) * (check.x - mouse_coord.x) +
                    (check.y - mouse_coord.y) * (check.y - mouse_coord.y) < 625)
                return Field::Coordinate(u - 1, d);
        }
    return Field::Coordinate(-1000, -1000);
}