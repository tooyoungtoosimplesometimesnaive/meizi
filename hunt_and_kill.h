#include "grid.h"
#include "cell.h"
#include <vector>

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

