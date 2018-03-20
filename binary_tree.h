
#include "grid.h"
#include "cell.h"
#include <vector>

class binary_tree {
public:
	void on(Grid& g)
	{
		for (auto itr = g.grid.begin(); itr != g.grid.end(); itr ++)
		{
			for (auto itc = itr->begin(); itc != itr->end(); itc ++)
			{
				std::vector<Cell*> n ({});
				if (itc->north)
					n.push_back(*itc);
				if (itc->east)
					n.push_back(*itc);

				int index = rand() % (n.size());
				Cell* neighbor = n[index];
				if (neighbor != nullptr)
					itc->link(neighbor);
			}
		}
	}
};

