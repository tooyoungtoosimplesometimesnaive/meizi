#ifndef WILSONS_H
#define WILSONS_H

#include "../grid.h"
#include "../cell.h"
#include "../rand.h"
#include <vector>
#include <algorithm>

class wilsons {
public:
	void on(Grid& g)
	{
		std::vector<Cell*> unvisited ({});
		for (auto itr = g.grid.begin(); itr != g.grid.end(); itr ++)
		{
			for (auto itc = itr->begin(); itc != itr->end(); itc ++)
			{
				unvisited.push_back((&(*itc)));
			}
		}

		int first_index = random(0, unvisited.size() - 1);
		// Cell* first = unvisited[first_index];
		unvisited.erase(unvisited.begin() + first_index);

		while (!unvisited.empty())
		{
			Cell* cell = unvisited[random(0, unvisited.size() - 1)];
			std::vector<Cell*> cell_path = { cell };

			while (std::find(unvisited.begin(), unvisited.end(), cell) != unvisited.end())
			{
				cell = cell->neighbors()[random(0, cell->neighbors().size() - 1)];

				auto pos = std::find(cell_path.begin(), cell_path.end(), cell);
				if (pos != cell_path.end())
				{
					cell_path.erase(pos, cell_path.end());
				} else {
					cell_path.push_back(cell);
				}

			}

			for (int i = 0; i < cell_path.size() - 1; i++)
			{
				
				auto current = cell_path[i];
				auto next = cell_path[i + 1];
				current->link(next);
				auto n = std::find(unvisited.begin(), unvisited.end(), current);
				unvisited.erase(n);
			}
		}
	}
};
#endif
