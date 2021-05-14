#pragma once

#include "game_fight.h"
#include "text.h"
#include "window_interface.h"
#include "gui_objects.h"
#include "log.h"
#include "gui_objects_factory.h"
#include "settings.h"
#include "sprite_storage.h"


class Game_drawer
{
public:
    explicit Game_drawer(Game_fight* game,
                         Gui_objects_abstract_factory* factory,
                         Window_interface* window,
                         Settings* settings);
public:
    void work();
private:
    void draw();
    void event_movemouse();
    void event_pressmouse(); // only one object
    void event_presskey(int key);
private:
    Game_fight* game;
    Gui_objects_abstract_factory* factory;
    Window_interface* window;
    gi::Texture* t_background;
    gi::Sprite* s_background;
    Settings* settings;
    Game_drawer_field sprite_drawer;
};