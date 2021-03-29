#include "../include/interactive_fiction.h"

#include <fstream>

Interactive_fiction::Interactive_fiction(const std::string& file_path)
{
	std::ifstream in(file_path);
	
	int count;
	in >> condition >> count;

	std::string name;
	int targets_number;

	while (count--)
	{
		Condition vsp;
		in >> name >> vsp.message >> targets_number;
		vsp.ways.resize(targets_number);
		for (int i = 0; i != targets_number; ++i)
			in >> vsp.ways[i].name >> vsp.ways[i].target;
		for (auto& it : vsp.message)
			if (it == '_')
				it = ' ';
			else if (it == '@')
				it = '\n';
		for (auto& it : vsp.ways)
			for (auto& i : it.name)
				if (i == '_')
					i = ' ';
		conditions[name] = std::move(vsp);
	}

	in.close();
}

void Interactive_fiction::press(int target_position)
{
	if (target_position >= 0 && target_position < conditions[condition].ways.size())
	{
		last_condition = condition;
		last_target = conditions[condition].ways[target_position].name;;
		condition = conditions[condition].ways[target_position].target;
	}

	message_size = 1;
	for (auto& it : conditions[condition].message)
		if (it == '\n')
			++message_size;
}