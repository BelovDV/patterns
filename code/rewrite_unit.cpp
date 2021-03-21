
// TODO ERROR HANDLING!!!

#include<fstream>
#include<iostream>
#include<vector>

#include"data_unit.h"

using std::vector;
using std::string;
using Unit::Data;
using std::cin;
using std::cout;

const string file_name = "data_unit";

void read(vector<Data>& in)
{
	std::ifstream fin(file_name);
	Data vsp;
	while (fin >> vsp)
		in.push_back(vsp);
	fin.close();
}

void write(const vector<Data>& out)
{
	std::ofstream fout(file_name);
	for (auto it : out)
		fout << it << '\n';
	fout.close();
}

void print(const vector<Data>& out)
{
	system("cls");
	cout.clear();
	cout << Data::description << "\n\n";
	for (int i = 0; i != out.size(); ++i)
		cout << i << '\t' << out[i] << '\n';
}

void work()
{
	vector<Data> in;
	read(in);

	/*while (true)
	{
		print(in);
		cout << "\nCommand options:\n";
		cout << "exit\n";
		cout << "swap number_1 number_2\n";
		cout << "delete number\n";
		cout << "add Data\n\n";
		char command = 0;
		while (!command)
		{
			string s;
			cin >> s;
			if (s == "exit")	command = 1;
			else if (s == "swap") command = 2;
			else if (s == "delete") command = 3;
			else if (s == "add") command = 4;
			else cout << "Wrong command. Try again.\n";
		}
		if (command == 1) 
			break;
		if (command == 2)
		{
			int n1 = -1, n2 = -1, vsp1, vsp2;
			while (n1 == -1 || n2 == -1)
			{
				cin >> vsp1 >> vsp2;
				if (vsp1 < 0 || vsp2 < 0 || vsp1 >= in.size() || vsp2 >= in.size())
				{
					cout << "Wrong input. Try again.\n";
					cin.clear();
					std::cin.ignore(32767, '\n');
				}
			}
			std::swap(in[n1], in[n2]);
			cin.clear();
			std::cin.ignore(32767, '\n');
		}
		else if (command == 3)
		{
			int n = -1, vsp;
			while (n == -1)
			{
				cin >> vsp;
				if (vsp < 0 || vsp >= in.size())
				{
					cout << "Wrong input. Try again.\n";
					cin.clear();
					std::cin.ignore(32767, '\n');
				}
			}
			in.erase(in.begin() + n);
		}
		else if (command == 4)
		{
			Data vsp;
			while (true)
			{
				std::cin.ignore(32767, '\n');
				cin.clear();
				cin >> vsp;
				if (cin.fail())
					cout << "Wrong input. Try again.\n";
				else
					break;
			}
			cin.clear();
			std::cin.ignore(32767, '\n');
			in.push_back(vsp);
		}
	}*/


	vector<Data> copy = in;
	while (true)
	{
		print(copy);
		cout << "\nCommand options:\n";
		cout << "exit\n";
		cout << "swap number_1 number_2\n";
		cout << "delete number\n";
		cout << "resert\n";
		cout << "add Data\n\n";
		char command = 0;
		while (!command)
		{
			string s;
			cin >> s;
			if (s == "exit")	command = 1;
			else if (s == "swap") command = 2;
			else if (s == "delete") command = 3;
			else if (s == "add") command = 4;
			else if (s == "resert") command = 5;
			else cout << "Wrong command. Try again.\n";
		}
		if (command == 1)
			break;
		if (command == 2)
		{
			int n1 = -1, n2 = -1;
			cin >> n1 >> n2;
			std::swap(copy[n1], copy[n2]);
			cin.clear();
		}
		else if (command == 3)
		{
			int n = -1;
			cin >> n;
			cin.clear();
			copy.erase(copy.begin() + n);
		}
		else if (command == 4)
		{
			Data vsp;
			cin >> vsp;
			cin.clear();
			copy.push_back(vsp);
		}
		else if (command == 5)
			copy = in;
	}

	write(copy);
}

int main()
{
	work();
	return 0;
}