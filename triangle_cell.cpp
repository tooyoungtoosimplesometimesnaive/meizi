#include "triangle_cell.h"
#include <vector>

bool Triangle_cell::upright()
{
	return (row + colum ) % 2 == 0;
}

std::vector<Triangle_cell*> Triangle_cell::neighbors()
{
	std::vector<Triangle_cell*> list ({});
	if (west)
		list.push_back(west);
	if (east)
		list.push_back(ccw);
	if (!upright() && north)
		list.push_back(north);
	if (upright() && south)
		list.push_back(south);
	return list;
}
