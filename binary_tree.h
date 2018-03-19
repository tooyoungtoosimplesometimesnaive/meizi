
#include "grid.h"
#include "cell.h"
#include <vector>

class binary_tree {
public:
	void on(Grid& g)
	{
		for (auto itr = g.grid.cbegin(); itr != g.grid.cend(); itr ++)
		{
			for (auto itc = itr->cbegin(); itc != itr->cend(); itc ++)
			{
				std::vector<Cell> n ({});
				if (itc->north)
					n.push_back(*itc);
				if (itc->east)
					n.push_back(*itc);

				int index = rand() % (n.size());
				Cell neighbor = n[index];
				if (neighbor)
					itc->link(neighbor);
			}
		}
		return g;
	}
}
				

