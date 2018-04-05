#ifndef RECURSIVE_BACK_TRACKER_H
#define RECURSIVE_BACK_TRACKER_H

#include "grid.h"
#include "cell.h"
#include "rand.h"
#include <vector>
#include <stack>

class recursive_back_tracker {
public:
	void on(Grid& g)
	{
		Cell * start_at = g.random_cell();
		std::stack<Cell*> s;
		s.push(start_at);
		while (!s.empty())
		{
			Cell * current = s.top();
			std::vector<Cell*> neighbors({});
			auto n = current->neighbors();

			for (auto it = n.begin(); it != n.end(); ++it)
			{
				if ((*it)->links.empty())
				{
					neighbors.push_back(*it);
				}
			}
			
			if (neighbors.empty())
			{
				s.pop();
			} else {
				int r = random(0, neighbors.size() - 1);
				auto neighbor = neighbors[r];
				current->link(neighbor);
				s.push(neighbor);
			}

		}
	}
};
#endif

