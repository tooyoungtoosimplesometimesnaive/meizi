#ifndef TRIANGLE_CELL_H
#define TRIANGLE_CELL_H

#include <vector>
#include "cell.h"

class Triangle_cell : public Cell
{
public:
	Triangle_cell(int row, int column) : Cell(row, column) {}
	
	std::vector<Triangle_cell*> neighbors();

	bool upright();

};
#endif
