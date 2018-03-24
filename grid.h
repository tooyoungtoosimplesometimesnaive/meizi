#ifndef GRID_H
#define GRID_H

#include <vector>
#include <ostream>
#include <string>
#include "cell.h"

class Grid {
public:
	friend std::ostream & operator<<(std::ostream &os, const Grid& g);
	Grid(int r, int c) : rows(r), columns(c)
	{
		grid = prepare_grid();
		configure_cells();
	}

	Cell* at(int row, int column);

	Cell* random_cell();

	int size() { return rows * columns; }
	void to_img(int cell_size = 10);
	std::string contents_of(Cell *cell);

	int rows;
	int columns;
	std::vector<std::vector<Cell>> grid;
private:
	std::vector<std::vector<Cell>> prepare_grid();
	void configure_cells();
};

#endif
