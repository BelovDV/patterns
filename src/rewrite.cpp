#include"../include/rewrite.h"

#include<iostream>
#include<cstdlib>

using std::cin;
using std::cout;
using std::string;

// ===== // ===== // ===== // ===== // ===== //

void Rewrite::work()
{
	while (cond != Condition::exit)
	{
		if (cond == Condition::start) dialogue_start();
		if (cond == Condition::races) dialogue_races();
		if (cond == Condition::classes) dialogue_classes();
		if (cond == Condition::units) dialogue_units();
	}
}

// ===== // ===== // ===== // ===== // ===== //

void Rewrite::dialogue_start()
{
	message_start();
	cout << "\nHere and further you can also"
		<< " print 'exit' to leave this level\n\n";
	
	string input;
	cin >> input;
	cin.ignore(32676, '\n');
	while (input != "exit" && input != "1" && input != "2" && input != "3")
	{
		system("cls");
		message_start();
		message_error_0(input);
		cin >> input;
		cin.ignore(32676, '\n');
	}
	if (input == "exit")
		cond = Condition::exit;
	else if (input == "1")
		cond = Condition::races;
	else if (input == "2")
		cond = Condition::classes;
	else if (input == "3")
		cond = Condition::units;
	system("cls");
}

void Rewrite::dialogue_races()
{
	string command, value, value_2;
	while (true)
	{
		system("cls");
		message_races();
		print_races();
		command = value = value_2 = "";
		cin >> command;
		if (check_int(command, -1) > 0 && check_int(command, -1) <= 3)
			cin >> value;
		if (command == "3")
			cin >> value_2;
		cin.ignore(32676, '\n');
		if (command == "1" && race_id.find(value) == race_id.end())
		{
			races.push_back(Data::Race::Data({ number_race, value }));
			race_id[value] = number_race;
			++number_race;
			units.push_back(std::vector<Data::Unit::Data>());
		}
		else if (command == "2" && check_int(value, -1) >= 0 &&
			check_int(value, -1) < number_race)
		{
			int a = check_int(value, -1), b = number_race - 1;
			std::swap(races[a].name, races[b].name);
			std::swap(race_id[races[a].name], race_id[races[b].name]);
			std::swap(units[a], units[b]);
			--number_race;
			race_id.erase(race_id.find(races[number_race].name));
			units.pop_back();
			races.pop_back();
		}
		else if (command == "3" && check_int(value, -1) >= 0 &&
			check_int(value, -1) < number_race &&
			check_int(value_2, -1) >= 0 &&
			check_int(value_2, -1) < number_race)
		{
			int a = check_int(value, -1), b = check_int(value_2, -1);
			std::swap(races[a].name, races[b].name);
			std::swap(race_id[races[a].name], race_id[races[b].name]);
			std::swap(units[a], units[b]);
		}
		else if (command == "exit")
			break;
		else
			message_error_0(command + ' ' + value),
			system("pause");
	}
	system("cls");
	cond = Condition::start;
}

void Rewrite::dialogue_classes()
{
	print_classes();
	system("pause");

	system("cls");
	cond = Condition::start;
}

void Rewrite::dialogue_units()
{
	print_units();
	system("pause");

	system("cls");
	cond = Condition::start;
}

// ===== // ===== // ===== // ===== // ===== //

void Rewrite::message_start()
{
	cout
		<< "This is application for configuration "
		<< Data::Constances::_file_name << " file.\n"
		<< "Choose the section you want to see:\n\n"

		<< "1:\traces\n"
		<< "2:\tclasses\n"
		<< "3:\tunits\n";
}

void Rewrite::message_races()
{
	cout
		<< "This is menu for changing races\n"
		<< "Available commands:\n\n"
		<< "1:\tadd 'name'\n"
		<< "2:\tdelete 'id'\n"
		<< "3:\tswap 'id_1' 'id_2'\n"
		<< "\n";
}

void Rewrite::message_classes()
{
}

void Rewrite::message_units()
{
	cout
		<< "1:\tadd 'race' 'name' '10 int' 'bitset<2>' '3 int'\n"
		<< "2:\tdelete 'id'"
		<< '\n';
}

void Rewrite::message_error_0(const string& input)
{
	cout
		<< "\nYour input: '"
		<< input
		<< "' was incorrect. Try again.\n\n";
}

void Rewrite::message_error_1()
{
	cout << "\nYour input was incorrect. Try again.\n";
}

// ===== // ===== // ===== // ===== // ===== //

void Rewrite::print_races()
{
	for (auto& iter : races)
		cout << iter << '\n';
	cout << '\n';
}

void Rewrite::print_classes()
{
	for (auto& iter : classes)
		cout << iter << '\n';
	cout << '\n';
}

void Rewrite::print_units()
{
	for (auto& iter : units)
		if (iter.size())
		{
			cout << iter[0].race << '\n';
			for (auto& it : iter)
				cout << '\t' << it << '\n';
		}
	cout << '\n';
}

// ===== // ===== // ===== // ===== // ===== //

int Rewrite::check_int(const string& s, int def)
{
	int x = std::atoi(s.c_str());
	if (std::to_string(x) != s)
		return def;
	return x;
}

// ===== // ===== // ===== // ===== // ===== //