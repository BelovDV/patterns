#pragma once

#include <string>
#include <vector>
#include <unordered_map>

class Interactive_fiction
{
public:
	struct Condition
	{
		struct Cross
		{
			std::string name;
			std::string target; // apply is reserved
		};
		struct List
		{
			std::string name;
			std::vector<std::string> values;
		};
		std::string message;
		std::vector<Cross> ways;
		std::vector<List> lists;
	};
public:
	Interactive_fiction(const std::string& file_path);
public:
	void press(int target_number);
	void forget();

	const Condition& get() { return conditions[position]; }
protected:
	std::unordered_map<std::string, Condition> conditions; // exit is reserved
	std::string position;
	int chosen_list = -1;
	std::vector<std::string*> condition;
	std::vector<std::string*> last_condition;
	std::string last_position;
	std::string last_target_name;
};