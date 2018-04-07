#include "masked_grid.h"


std::vector<std::vector<Cell>> Maksed_grid::prepare_grid()
{
	std::vector<std::vector<Cell>> v({});
	for (int i = 0; i < rows; i++)
	{
		std::vector<Cell> vv({});
		for (int j = 0; j < columns; j++)
		{
			if (mask.at(i, j)) {
				Cell c(i, j);
				vv.push_back(c);
			}

		}
		v.push_back(vv);
	}

	return v;
}

Cell* Masked_grid::random_cell()
{
	auto p = mask.random_location();
	return at(p.first, p.second);
}
