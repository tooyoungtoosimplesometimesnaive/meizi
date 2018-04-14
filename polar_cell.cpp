#include <vector>
#include "polar_cell.h"

std::vector<Polar_cell*> neighbors()
{
	std::vector<Polar_cell*> list ({});
	if (cw)
		list.push_back(cw);
	if (ccw)
		list.push_back(ccw);
	if (inward)
		list.push_back(inward);
	list.insert(list.end(), outward.begin(), outward.end());
	return list;
}

