#include "grid.h"
#include "cell.h"
#include <vector>
#include <iostream>

int uniform_dist(int start, int end)// all inclusive
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(start, end);
	return dist(gen);
}
	
class hunt_and_kill {
public:
	void on(Grid& g)
	{
		Cell * current = g.random_cell();
		while (current != nullptr)
		{
			std::vector<Cell*> unvisited_neighbors({});
			for (auto it = current->neighbors().begin(); it != current->neighbors().end(); it++)
			{
				std::cout << "here in the initial loop" << std::endl;
				std::cout << (*it)->links.empty() << std::endl;
				std::cout << unvisited_neighbors.size() << std::endl;
				if ((*it)->links.empty())
				{
					unvisited_neighbors.push_back(*it);
				}
			}

			if (!unvisited_neighbors.empty())
			{
				std::cout << "here" << std::endl;
				//select a random neighbor
				// current = neighbor
				int r = uniform_dist(0, unvisited_neighbors.size() - 1);
				auto neighbor = unvisited_neighbors[r];
				current->link(neighbor);
				current = neighbor;
			} else {
				current = nullptr;
				for (auto itr = g.grid.begin(); itr != g.grid.end(); itr++)
				{
					for (auto itc = itr->begin(); itc != itr->end(); itc++)
					{
				std::cout << "here in the loop" << std::endl;
						std::vector<Cell*> visited_neighbors({});
						for (auto n = itc->neighbors().begin(); n != itc->neighbors().end(); n++)
						{
							if (!(*n)->links.empty()) {
								visited_neighbors.push_back(*n);
							}
						}

						if (itc->links.empty() && !visited_neighbors.empty())
						{
							current = &(*itc);
							// select a random neighbor
							int r = uniform_dist(0, visited_neighbors.size() - 1);
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

