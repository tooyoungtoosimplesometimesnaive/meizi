#ifndef GRID_H
#define GRID_H

#include <vector>
#include "cell.h"

class grid {
public:
	grid(int r, int c) : rows(r), columns(c)
	{
		grid = prepare_grid();
		configure_cells();
	}

	cell at(int row, int column);

	cell random_cell();

	int size() { return rows * columns; }

	int rows;
	int columns;
	std::vector<std::vector<cell>> grid;
private:
	std::vector<std::vector<cell>> prepare_grid();
	void configure_cells();
}

#endif
