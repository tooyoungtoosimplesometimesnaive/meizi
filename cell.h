#ifndef CELL_H
#define CELL_H

#include <vector>

class Cell {
public:
	friend bool operator==(Cell& lhs, Cell& rhs);
	Cell(int r, int c) : row(r), column(c), links({}),
		north(nullptr), west(nullptr), south(nullptr), east(nullptr) {}

	void link(Cell* c, bool bidirectionally = true);
	void unlink(Cell* c, bool bidirectionally = true);

	// linked?
	bool is_linked(const Cell* c) const;
	
	// get the neighbors
	std::vector<Cell*> neighbors();

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
