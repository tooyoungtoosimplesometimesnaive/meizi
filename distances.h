#ifndef DISTANCES_H
#define DISTANCES_H

#include <unordered_map>
#include "Cell_hash.h"
#include "cell.h"

class Distances {
public:
	Distances() {}
	Distances(Cell& c): root(c)
	{
		cells[c] = 0;
	}
	Distances path_to(Cell goal);

	Cell root;
	// need to have a map of cells and distances.
	std::unordered_map<Cell, int, Cell_hash> cells;
};
#endif
