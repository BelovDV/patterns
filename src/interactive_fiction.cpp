#include "../include/interactive_fiction.h"
#include "../include/log.h"

#include <fstream>

Interactive_fiction::Interactive_fiction(const std::string& file_path)
{
	std::ifstream in(file_path);
	
	in >> position;

	std::string name;
	int count;

	while (in >> name)
	{
		for (auto& it : name)
			if (it == '_') it = ' ';
		Condition vsp;
		in >> vsp.message >> count;
		for (auto& it : vsp.message)
			if (it == '_') it = ' ';
			else if (it == '@') it = '\n';
		vsp.ways.resize(count);
		for (auto& it : vsp.ways)
			in >> it.name >> it.target;
		for (auto& iter : vsp.ways)
		{
			for (auto& it : iter.name)
				if (it == '_') it = ' ';
			for (auto& it : iter.target)
				if (it == '_') it = ' ';
		}
		in >> count;
		vsp.lists.resize(count);
		for (auto& iter : vsp.lists)
		{
			in >> iter.name >> count;
			iter.values.resize(count);
			for (auto& it : iter.values)
				in >> it;
			for (auto& iterator : iter.values)
				for (auto& it : iterator)
					if (it == '_') it = ' ';
		}
		conditions[name] = vsp;
	}
}

void Interactive_fiction::press(int tp)
{
	Condition& vsp = conditions[position];

	int list_size = chosen_list == -1 ? 0 : vsp.lists[chosen_list].values.size();
	if (tp < 0 || tp >= vsp.ways.size() + vsp.lists.size() + list_size)
		Log::add("IF::press", "didn't find target_position");

	if (tp < vsp.ways.size()) // (1)
	{
		last_target_name = vsp.ways[tp].name;
		last_position = position;
		position = vsp.ways[tp].target;
		if (conditions.find(position) == conditions.end())
			Log::add("IF::press", "wrong target");
		last_condition = condition;
		condition.resize(conditions[position].lists.size());
		chosen_list = -1;
		for (int i = 0; i != conditions[position].lists.size(); ++i)
			condition[i] = &conditions[position].lists[i].name;
		return;
	}
	tp -= vsp.ways.size();
	if (tp < chosen_list) // (2)
	{
		chosen_list = tp;
		return;
	}
	if (tp == chosen_list) // (3)
	{
		chosen_list = -1;
		return;
	}
	if (list_size && tp <= chosen_list + list_size) // (4)
	{
		condition[chosen_list] = &vsp.lists[chosen_list].values[tp - chosen_list - 1];
		chosen_list = -1;
		return;
	}
	chosen_list = tp - list_size; // (5)
}

void Interactive_fiction::forget()
{
	last_position = "";
	last_target_name = "";
}
/*
example:
0	0	(1)
1	1	(1)
2	2	(1)
30	 0	(2)
41	 1	(2)
52	 2	(3)
63	  0	(4)
74	  1	(4)
85	  2	(4)
96	 3	(5)
*/