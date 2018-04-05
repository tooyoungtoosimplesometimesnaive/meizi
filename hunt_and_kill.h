#ifndef HUNT_AND_KILL_H
#define HUNT_AND_KILL_H

#include "grid.h"
#include "cell.h"
#include "rand.h"
#include <vector>

class hunt_and_kill {
public:
	void on(Grid& g)
	{
		Cell * current = g.random_cell();
		while (current != nullptr)
		{
			std::vector<Cell*> unvisited_neighbors({});
			auto n = current->neighbors();

			for (auto it = n.begin(); it != n.end(); ++it)
			{
				if ((*it)->links.empty())
				{
					unvisited_neighbors.push_back(*it);
				}
			}

			if (!unvisited_neighbors.empty())
			{
				int r = random(0, unvisited_neighbors.size() - 1);
				auto neighbor = unvisited_neighbors[r];
				current->link(neighbor);
				current = neighbor;
			} else {
				current = nullptr;
				for (auto itr = g.grid.begin(); itr != g.grid.end(); itr++)
				{
					for (auto itc = itr->begin(); itc != itr->end(); itc++)
					{
						std::vector<Cell*> visited_neighbors({});
						auto neighbors = itc->neighbors();
						for (auto itn = neighbors.begin(); itn != neighbors.end(); itn++)
						{
							if (!(*itn)->links.empty()) {
								visited_neighbors.push_back(*itn);
							}
						}

						if (itc->links.empty() && !visited_neighbors.empty())
						{
							current = &(*itc);
							// select a random neighbor
							int r = random(0, visited_neighbors.size() - 1);
							auto neighbor = visited_neighbors[r];
							current->link(neighbor);

							break;
						}

					}
				}
			}
		}
	}
};
#endif

