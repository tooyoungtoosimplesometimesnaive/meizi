#include "masked_grid.h"
#include "grid.h"

void Masked_grid::drop_cells()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (!mask.at(i, j)) {
				auto c = at(i, j);
				c->north = nullptr;
				c->west = nullptr;
				c->south = nullptr;
				c->east = nullptr;

				auto c_north = at(i - 1, j);
				if (c_north)
					c_north->south = nullptr;
				auto c_south = at(i + 1, j);
				if (c_south)
					c_south->north = nullptr;
				auto c_west = at(i, j - 1);
				if (c_west)
					c_west->east = nullptr;
				auto c_east = at(i, j + 1);
				if (c_east)
					c_east->west = nullptr;
			}

		}
	}
}

Cell* Masked_grid::random_cell()
{
	auto p = mask.random_location();
	return at(p.first, p.second);
}

int Masked_grid::size()
{
	return mask.count();
}

