#pragma once

#include"database.h"

class Rewrite : public Database
{
	enum class Condition
	{
		start,
		races,
		classes,
		units,
		exit
	};
	Condition cond = Condition::start;
public:
	Rewrite() {}
public:
	void work();
private:
	void dialogue_start();
	void dialogue_races();
	void dialogue_classes();
	void dialogue_units();

	void message_start();
	void message_races();
	void message_classes();
	void message_units();
	void message_error_0(const std::string& input);
	void message_error_1();

	void print_races();
	void print_classes();
	void print_units();
	
	int check_int(const std::string& s, int def);
};