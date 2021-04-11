#include "../include/start_menu.h"
#include "../include/gui.h"
#include "../include/graphic.h"

int main()
{
	Settings settings("../data/settings.txt");
	Start_menu menu(settings);
	Graphic graphic;
	GUI gui(&menu, &graphic);
	gui.work();
	return 0;
}