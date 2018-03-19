#ifndef GRID_H
#define GRID_H

#include <vector>
#include "cell.h"

class Grid {
public:
	Grid(int r, int c) : rows(r), columns(c)
	{
		grid = prepare_grid();
		configure_cells();
	}

	Cell& at(int row, int column);

	Cell random_cell();

	int size() { return rows * columns; }

	int rows;
	int columns;
	std::vector<std::vector<Cell>> grid;
private:
	std::vector<std::vector<Cell>> prepare_grid();
	void configure_cells();
};

#endif
