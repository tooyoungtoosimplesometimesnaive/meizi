
#include "grid.h"
#include "cell.h"
#include <vector>
#include <random>

class sidewinder {
public:
	void on(Grid& g)
	{
		for (auto itr = g.grid.begin(); itr != g.grid.end(); itr ++)
		{
			std::vector<Cell*> run ({});
			for (auto itc = itr->begin(); itc != itr->end(); itc ++)
			{
				run.push_back(&(*itc));
				bool at_eastern_boundary = itc->east == nullptr;
				bool at_northern_boundary = itc->north == nullptr;

				std::random_device rd;
				std::mt19937 gen(rd());
				std::uniform_int_distribution<int> dist(0, 1);
				bool should_close_out = at_eastern_boundary ||
					(!at_northern_boundary && dist(gen) == 0);

				if (should_close_out) {
					std::uniform_int_distribution<int> member_dist(0, run.size() - 1);
					Cell* member = run[member_dist(gen)];
					if (member->north)
						member->link(member->north);
					run.clear();
				}
				else {
					itc->link(itc->east);
				}
			}
		}
	}
};

