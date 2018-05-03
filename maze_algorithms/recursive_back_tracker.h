#ifndef RECURSIVE_BACK_TRACKER_H
#define RECURSIVE_BACK_TRACKER_H

#include "../cell.h"
#include "../rand.h"
#include <vector>
#include <stack>

#include <iostream>

template<typename Grid_Type>
class recursive_back_tracker {
public:
	void on(Grid_Type& g)
	{
		auto * start_at = g.random_cell();

		std::cout << "start at : " << start_at->row << " " << start_at->column << std::endl;
		std::stack<decltype(start_at)> s;

		s.push(start_at);
		while (!s.empty())
		{
			auto * current = s.top();
			std::vector<decltype(start_at)> neighbors({});
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

