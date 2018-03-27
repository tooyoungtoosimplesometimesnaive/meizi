#include <utility>
#include "distances.h"

/**
 * This method should be called after the Cell#disntacnes()
 */
Distances Distances::path_to(Cell goal)
{
	Cell current = goal;
	Distances breadcrumbs(root);
	breadcrumbs.cells[current] = cells[current];

	while (current != root)
	{
		for (auto it = current.links.begin(); it != current.links.end(); it ++)
		{
			if (cells[**it] < cells[current])
			{
				breadcrumbs.cells[**it] = cells[**it];
				current = **it;
				break;
			}
		}
	}
	return breadcrumbs;
}

std::pair<Cell, int> Distances::max_distance()
{
	int max_dist = 0;
	Cell max_cell = root;
	for (auto it = cells.begin(); it != cells.end(); it++)
	{
		int d = it->second;
		if (d > max_dist)
		{
			max_cell = it->first;
			max_dist = d;
		}
	}
	return std::make_pair(max_cell, max_dist);
}
