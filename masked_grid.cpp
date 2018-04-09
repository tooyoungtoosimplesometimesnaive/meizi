#include "masked_grid.h"
#include "grid.h"
#include <iostream>


std::vector<std::vector<Cell>> Masked_grid::prepare_grid()
{
	std::cout << "in here " << std::endl;
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
	std::cout << "here in random " << std::endl;
	auto p = mask.random_location();
	return at(p.first, p.second);
}
