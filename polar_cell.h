#ifndef POLAR_CELL_H
#define POLAR_CELL_H

#include <vector>
#include "cell.h"

class Polar_cell : public Cell
{
public:
	Polar_cell(int row, int column) : Cell(row, column), outward({}) {}
	
	std::vector<Polar_cell*> neighbors();

	Polar_cell * cw, * ccw, * inward;
	std::vector<Polar_cell*> outward;
};
#endif
