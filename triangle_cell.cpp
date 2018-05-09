#include "triangle_cell.h"
#include <vector>

bool Triangle_cell::upright()
{
	return (row + column) % 2 == 0;
}

std::vector<Triangle_cell*> Triangle_cell::neighbors()
{
	std::vector<Triangle_cell*> l ({});
	if (west)
		l.push_back(west);
	if (east)
		l.push_back(east);
	if (!upright() && north)
		l.push_back(north);
	if (upright() && south)
		l.push_back(south);
	return l;
}
