#include "../include/start_menu.h"
#include "../include/gui.h"

int main()
{
	Settings settings("../data/settings.txt");
	Start_menu menu(settings);
	GUI gui(&menu);
	gui.work();
	return 0;
}