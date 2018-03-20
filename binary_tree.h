
#include "grid.h"
#include "cell.h"
#include <vector>
#include <random>

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

				std::random_device rd;
				std::mt19937 gen(rd());
				std::uniform_int_distribution<int> dist(0, n.size() - 1);
				int index = dist(gen);
				if (n[index] != nullptr)
					itc->link(n[index]);
			}
		}
	}
};

