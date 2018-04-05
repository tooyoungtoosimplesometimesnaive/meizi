#ifndef SIDEWINDER_H
#define SIDEWINDER_H

#include "grid.h"
#include "cell.h"
#include "rand.h"
#include <vector>

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

				bool should_close_out = at_eastern_boundary ||
					(!at_northern_boundary && random(0, 1) == 0);

				if (should_close_out) {
					Cell* member = run[random(0, run.size() - 1)];
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
#endif
