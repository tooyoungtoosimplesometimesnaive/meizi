#ifndef DISTANCES_H
#define DISTANCES_H

#include <unordered_map>
#include "Cell_hash.h"
#include "cell.h"

class Distances {
public:
	Distances(Cell& c): root(c)
	{
		cells[c] = 0;
	}

	Cell root;
	// need to have a map of cells and distances.
	std::unordered_map<Cell, int, Cell_hash> cells;
};
#endif
