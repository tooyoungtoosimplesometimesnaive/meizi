#include "mask.h"
#include <utility>

bool Mask::at(int row, int column)
{
	if (row >= 0 && row < rows && column >=0 && column < columns)
	{
		return bits[row][column];
	}
	else
	{
		return false;
	}
}

int Mask::count()
{
	int c = 0;
	for (auto itr = bits.begin(); itr != bits.end(); itr++)
	{
		for (auto itc = itr->begin(); itc != itr->end(); itr++)
		{
			if (*itc)
			{
				c++;
			}
		}
	}
	return c;
}

std::pair<int, int> Mask::random_loaction()
{
	int r = 0, c = 0;
	do {
		r = random(0, rows - 1);
		c = random(0, columns - 1);
	} while (!bits[r][c]);
	return std::make_pair(r, c);
}

