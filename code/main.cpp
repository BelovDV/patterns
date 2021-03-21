#include<iostream>
#include<vector>

#include"choosing.h"
#include"AI.h"

class AI_test : public Chooser
{
	virtual Field_choice get_AI_choice(const Field& field) { return Field_choice(); }
};

using std::cin;
using std::cout;
using std::string;

void print(std::vector<Unit::Data>& l1, std::vector<Unit::Data>& l2)
{
	cout << "Available:\n";
	for (auto& iter : l1)
		cout << iter << '\n';
	cout << "\nChosen:\n";
	for (auto& iter : l2)
		cout << iter << '\n';
}

void work()
{
	AI_test AI;
	Choosing chose(AI);
	string in;
	
	cout << "Choose race from:\n";
	cout << "1: \t\tthirst\n";
	cout << "any else:\tsecond\n";
	cin >> in;
	cin.clear();
	cout.clear();
	system("cls");
	if (in == "1")
	{
		chose.set_race(Gamer_types::Race::thirst);
		cout << "You chosen thirst race\n";
	}
	else
	{
		chose.set_race(Gamer_types::Race::second);
		cout << "You chosen second race\n";
	}
	system("pause");

	cout << "Choose class from:\n";
	cout << "1: warrior\t\t\n";
	cout << "2: trader\t\t\n";
	cout << "any else:\tmagician\n";
	cin >> in;
	cin.clear();
	cout.clear();
	system("cls");
	if (in == "1")
	{
		chose.set_class(Gamer_types::Class::warrior);
		cout << "You chosen warrior\n";
	}
	else if (in == "2")
	{
		chose.set_class(Gamer_types::Class::trader);
		cout << "You chosen trader\n";
	}
	else
	{
		chose.set_class(Gamer_types::Class::magician);
		cout << "You chosen magician\n";
	}
	system("pause");
	system("cls");

	cout << Unit::Data::description << "\n\n";
	auto list = chose.get_units_list();
	auto chos = chose.get_units_list_chosen();
	while (true)
	{
		system("cls");
		print(list, chos);
		cout << "\nChose from command:\n";
		cout << "add number\n";
		cout << "modify number\n";
		cout << "anything else - enough\n";
		cin >> in;
		if (in == "add")
		{
			int vsp;
			cin >> vsp;
			cin.clear();
			chose.choose_unit(vsp);
			chos = chose.get_units_list_chosen();
		}
		else if (in == "modify")
		{
			int vsp;
			cin >> vsp;
			cin.clear();
			cout << "0: change_cost_A\n";
			cout << "1: change_cost_B\n";
			cout << "2: change_cost_C\n";
			cout << "3: change_dmin\n";
			cout << "4: change_dmax\n";
			cout << "any else: change_xp\n";
			int vsp2;
			cin >> vsp2;
			if (vsp2 < 0 || vsp2 > 4)
				vsp2 = 5;
			chose.modificate_unit(vsp, Gamer_types::Ability_class(vsp2));
		}
		else
		{
			system("cls");
			if (chose.get_money_A() >= 0 &&
				chose.get_money_B() >= 0 &&
				chose.get_money_C() >= 0 &&
				chose.get_money_M() >= 0)
				break;
			else
				cout << "You haven't enough money\n";
		}
	}
	cout << "As a result:\n\n";
	print(list, chos);
	system("pause");
}

string Unit::Info::description = "lvl att def dmin dmax hp spd init being costA costB costC";
string Unit::Data::description = "id race name " + Unit::Info::description;

int main()
{
	Gamer_types::init_class_ability_list();


	work();
	return 0;
}