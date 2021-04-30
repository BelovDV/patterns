#include "../include/start_menu.h"
#include "../include/gui.h"
#include "../include/graphic.h"
#include "../include/gui_objects_factory.h"

int main()
{
	Log::add("main", "begin");
	Settings settings("../data/settings.txt");
	Gui_objects_backtexture_factory factory("../data/image/vsp.jpeg");
	Start_menu menu(settings, &factory);
	Window graphic(settings.get_screen().x, settings.get_screen().y);
	GUI gui(&menu, &graphic, &settings);
	gui.work();
	return 0;
}