#include "distances.h"


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

