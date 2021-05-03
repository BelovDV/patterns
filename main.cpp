#include "start_menu.h"
#include "beginning.h"
#include "gui.h"
#include "graphic.h"
#include "gui_objects_factory.h"
#include "database_loader.h"

Database_loader database;

int main()
{
    database.load("../data/data");
    database.initialise();
	Log::add("main", "begin");
	Settings settings("../data/settings.txt");
	Gui_objects_rect_factory factory;
	Start_menu menu(settings, &factory);
    Position position;
	Beginning beginning(&factory, &position);
	Start_menu loading(settings, &factory);
	Window graphic(settings.get_screen().x, settings.get_screen().y);
	GUI gui(&menu, &beginning, &loading, &graphic, &settings);
	gui.work();
	return 0;
}