#ifndef ALDOUS_BRODER_H
#define ALDOUS_BRODER_H

#include "../grid.h"
#include "../cell.h"
#include "../rand.h"

#include <vector>

template<typename Grid_Type>
class aldous_broder {
public:
	void on(Grid_Type& g)
	{
		auto* cell = g.random_cell();
		int unvisited = g.rows * g.columns - 1;
		while (unvisited > 0)
		{
			auto neighbors = cell->neighbors();
			auto * neighbor = neighbors[random(0, neighbors.size() - 1)];

			if (neighbor->links.empty())
			{
				cell->link(neighbor);
				unvisited -= 1;
			}
			cell = neighbor;
		}
	}
};
#endif

