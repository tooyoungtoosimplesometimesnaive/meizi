#include <vector>
#include "grid.h"

std::vector<std::vector<cell>> grid::prepare_grid()
{
	std::vector<std::vector<cell>> v({});
	for (int i = 0; i < rows; i++)
	{
		std::vector<cell> vv({});
		for (int j = 0; j < columns; j++)
		{
			cell c(i, j);
			vv.push_back(c);

		}
		v.push_back(vv);
	}

	return v;
}


void grid::configure_cells()
{

}

cell grid::at(int row, int column)
{
}
