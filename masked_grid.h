#ifndef MASKED_GRID_H
#define MASKED_GRID_H

#include <vector>
#include "grid.h"
#include "mask.h"
#include "cell.h"

class Masked_grid : public Grid
{
public:
	Masked_grid(Mask m) : Grid(m.rows, m.columns), mask(m) {
		drop_cells();
	}

	// these are inherited from the base class.
	void drop_cells();

	int size();
	Cell* random_cell() override;

	Mask mask;

};

#endif
