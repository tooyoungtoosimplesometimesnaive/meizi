#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "../grid.h"
#include "../cell.h"
#include "../rand.h"
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
					n.push_back(itc->north);
				if (itc->east)
					n.push_back(itc->east);

				if (n.size() == 0)
					continue;

				int index = random(0, n.size() - 1);
				if (n[index] != nullptr)
					itc->link(n[index]);
			}
		}
	}
};
#endif
