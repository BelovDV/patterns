#pragma once

#include <string>
#include <vector>
#include <unordered_map>

class Interactive_fiction
{
public:
	struct Condition
	{
		struct Transition
		{
			std::string name;
			std::string target;
		};
		std::string message;
		std::vector<Transition> ways;
	};
public:
	Interactive_fiction(const std::string& file_path);
public:
	void press(int target_position);
	const Condition& get() { return conditions[condition]; }
	const std::string& get_condition() { return condition; }
	int get_message_size() { return message_size; }
	const std::string& get_last_condition() { return last_condition; }
	const std::string& get_last_target() { return last_target; }
private:
	std::unordered_map<std::string, Condition> conditions;
	std::string condition;
	int message_size = 1;
	std::string last_condition;
	std::string last_target;
};