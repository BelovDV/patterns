#include "../include/start_menu.h"
#include "../include/gui.h"
#include "../include/graphic.h"

int main()
{
	Settings settings("../data/settings.txt");
	Start_menu menu(settings);
	Window graphic(settings.get_screen().x, settings.get_screen().y);
	GUI gui(&menu, &graphic, &settings);
	gui.work();
	return 0;
}