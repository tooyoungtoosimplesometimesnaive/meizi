
#include "grid.h"
#include "cell.h"
#include <vector>
#include <random>

class aldous_broder {
public:
	void on(Grid& g)
	{
		Cell* cell = g.random_cell();
		int unvisited = g.rows * g.columns - 1;
		while (unvisited > 0)
		{
			auto neighbors = cell->neighbors();
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<int> dist(0, neighbors.size() - 1);
			Cell * neighbor = neighbors[dist(gen)];

			if (neighbor->links.empty())
			{
				cell->link(neighbor);
				unvisited -= 1;
			}
			cell = neighbor;
		}
	}
};

