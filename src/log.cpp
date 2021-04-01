#include "../include/log.h"

void Log::add(const std::string& source, const std::string& message)
{
	if (!out.is_open())
		std::cout << "ERROR!!!\n\n";
	if (to_console)
		std::cout << source << '\n' << message << "\n\n";
	if (to_file)
		out << source << '\n' << message << "\n\n";
}

std::ofstream Log::out = std::ofstream("log.txt");