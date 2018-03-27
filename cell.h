#ifndef CELL_H
#define CELL_H

#include <vector>
// #include "distances.h"
class Distances;

class Cell {
public:
	friend bool operator==(const Cell& lhs, const Cell& rhs);
	friend bool operator!=(const Cell& lhs, const Cell& rhs);

	Cell(){}
	Cell(int r, int c) : row(r), column(c), links({}),
		north(nullptr), west(nullptr), south(nullptr), east(nullptr) {}

	void link(Cell* c, bool bidirectionally = true);
	void unlink(Cell* c, bool bidirectionally = true);

	// linked?
	bool is_linked(const Cell* c) const;
	
	// get the neighbors
	std::vector<Cell*> neighbors();

	Distances distances();

	int row;
	int column;
	
	// links
	std::vector<Cell*> links;

	//
	Cell* north;
	Cell* west;
	Cell* south;
	Cell* east;
};

#endif
