#ifndef CELL_H
#define CELL_H

#include <vector>
#include <unordered_set>

class Cell {
public:
	Cell(int r, int c) : row(r), column(c), links({}) {}
	void link(Cell& c, bool bidirectionally = true);
	void unlink(Cell& c, bool bidirectionally = true);

	// linked?
	bool is_linked(Cell& c);
	
	// get the neighbors
	std::vector<Cell> neighbors();

	int row;
	int column;

	// links
	std::unordered_set<Cell> links;

	//
	Cell* north;
	Cell* west;
	Cell* south;
	Cell* east;
};

#endif
