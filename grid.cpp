#include <vector>
#include "grid.h"

std::vector<std::vector<Cell>> Grid::prepare_grid()
{
	std::vector<std::vector<Cell>> v({});
	for (int i = 0; i < rows; i++)
	{
		std::vector<Cell> vv({});
		for (int j = 0; j < columns; j++)
		{
			Cell c(i, j);
			vv.push_back(c);

		}
		v.push_back(vv);
	}

	return v;
}


void Grid::configure_cells()
{
	for (auto itr = grid.begin(); itr != grid.end(); itr++)
	{
		for (auto itc = itr->begin(); itc != itr->end(); itc++)
		{
			int r = itc->row;
			int c = itc->column;
			itc->north = &at(r - 1, c);
			itc->south = &at(r + 1, c);
			itc->west = &at(r, c - 1);
			itc->east = &at(r, c + 1);
		}
	}
}

Cell& Grid::at(int row, int column)
{
	if (row < 0 || row >= rows)
		return nullptr;
	if (column < 0 || column >= columns)
		return nullptr;
	return grid[row][column];
}


Cell Grid::random_cell()
{
	int r = rand() % rows;
	int c = rand() % columns;
	return at(r, c);
}

