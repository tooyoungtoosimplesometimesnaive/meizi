#ifndef MASKED_GRID_H
#define MASKED_GRID_H

#include <vector>
#include "grid.h"
#include "mask.h"
#include "cell.h"

class Masked_grid : public Grid
{
public:
	Masked_grid(Mask m) {}

	// these are inherited from the base class.
	std::vector<std::vector<Cell>> prepare_grid();

	int size();
	Cell* random_cell();

	Mask mask;

}

#endif
