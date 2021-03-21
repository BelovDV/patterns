#include"field.h"

bool operator<(const Coord& a, const Coord& b)
{
	if (a.a != b.a)
		return a.a < b.a;
	return a.b < b.b;
}