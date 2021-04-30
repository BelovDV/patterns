#pragma once

#include <fstream>
#include <iostream>

class Log
{
public:
	static void add(const std::string& source, const std::string& message);
private:
	static std::ofstream out;
	const static bool to_console = true;
	const static bool to_file = true;
};