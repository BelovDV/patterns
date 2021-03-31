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
	bool is_with_list() { return conditions[position].lists.size(); }
	int get_chosen_list() { return chosen_list; }
	const std::string& get_position() { return position; }
	const std::vector<std::string*>& get_condition() { return condition; }
	const std::string& get_message() { return conditions[position].message; }
	const std::vector<Condition::Cross> get_ways() { return conditions[position].ways; }
	const std::string& get_last_position() { return last_position; }
	const std::string& get_last_target_name() { return last_target_name; }
	const std::vector<std::string*> get_last_condition() { return last_condition; }
private:
	std::unordered_map<std::string, Condition> conditions; // exit is reserved
	std::string position;
	int chosen_list = -1;
	std::vector<std::string*> condition;
	std::vector<std::string*> last_condition;
	std::string last_position;
	std::string last_target_name;
};