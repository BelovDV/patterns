#include "game_drawer.h"
#include "database_loader.h"

Game_drawer::Game_drawer(Game_fight* game,
                         Gui_objects_abstract_factory* factory,
                         Window_interface* window,
                         Settings* settings) :
        game(game),
        factory(factory),
        window(window),
        t_background(gi::Texture::generate()),
        s_background(gi::Sprite::generate()),
        settings(settings),
        sprite_drawer(gi::Vector(settings->get_screen()))
{
    t_background->load("../data/image/back.jpeg");
    s_background->set_texture(*t_background);
    s_background->set_scale((double)settings->get_screen().x / settings->get_screen().x,
                            (double)settings->get_screen().y / settings->get_screen().y);
}

void Game_drawer::work()
{
    draw();

    while (window->is_open())
    {
        gi::Event event;
        while (window->poll_event(event))
        {
            if (event.type == gi::Event_type::mouse_moved)
                event_movemouse();
            else if (event.type == gi::Event_type::mouse_button_pressed)
                event_pressmouse();
            else if (event.type == gi::Event_type::key_pressed)
                event_presskey(event.keycode);

            draw();
        }

        if (game->get_position()->end())
            break;
    }
}

void Game_drawer::draw() {
    s_background->draw(*window);

    auto position = game->get_position();
    for (int u = -99; u != 99; ++u)
        for (int d = -99; d != 99; ++d) {
            auto cell = position->get_field().check_cell(Field::Coordinate(u, d));
            if (cell.terrain == Field::Grass)
                sprite_drawer.draw(Game_drawer_field::grass, Field::Coordinate(u, d), window);
        }

    for (int i = 0; i != 2; ++i)
        for (auto unit : position->get_units(Position::Player(i))) {
            int u = unit.second.get_coordinates().u;
            int d = unit.second.get_coordinates().d;
            sprite_drawer.draw
                    (Game_drawer_field::Images(database.get_units()[unit.second.get_id()].image_id),
                     Field::Coordinate(u, d), window);
        }

    sprite_drawer.draw(Game_drawer_field::hex_green, game->get_next_coordinate(), window);
    for (auto& it : game->get_possible_ways())
        sprite_drawer.draw(Game_drawer_field::hex_green, it, window);
    for (auto& it : game->get_possible_attack())
        sprite_drawer.draw(Game_drawer_field::hex_red, it, window);

    window->display();
}

void Game_drawer::event_movemouse() {

}

void Game_drawer::event_presskey(int key) {
    if (key == static_cast<int>(gi::Keycode::up)) sprite_drawer.change_coordinate({0, 30});
    if (key == static_cast<int>(gi::Keycode::right)) sprite_drawer.change_coordinate({-30, 0});
    if (key == static_cast<int>(gi::Keycode::down)) sprite_drawer.change_coordinate({0, -30});
    if (key == static_cast<int>(gi::Keycode::left)) sprite_drawer.change_coordinate({30, 0});

    if (key == static_cast<int>(gi::Keycode::space)) game->press(game->get_next_coordinate());
}

void Game_drawer::event_pressmouse() {
    auto coord = sprite_drawer.get_coord(window->get_mouse_position());
    game->press(coord);
}