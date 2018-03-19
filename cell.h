#ifndef CELL_H
#define CELL_H

#include <vector>
#include <unordered_set>

class cell {
public:
	cell(int r, int c) : row(r), column(c), links({}) {}
	void link(cell c, bool bidirectionally = true);
	void unlink(cell c, bool bidirectionally = true);

	// linked?
	bool is_linked(cell c);
	
	// get the neighbors
	std::vector<cell> neighbors();

	int row;
	int column;

	// links
	std::unordered_set<cell> links;

	//
	cell north;
	cell west;
	cell south;
	cell east;
}

#endif
