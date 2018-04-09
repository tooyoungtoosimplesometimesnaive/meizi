#include "mask.h"
#include "rand.h"
#include <utility>
#include <iostream>

Mask::Mask(int r, int c) : rows(r), columns(c), bits({}) {
	for (int i = 0; i < r; i++)
	{
		std::vector<bool> r(c, true);
		bits.push_back(r);
	}
}

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


void Mask::put(int row, int column, bool value)
{
	if (row >= 0 && row < rows && column >=0 && column < columns)
	{
		bits[row][column] = value;
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

std::pair<int, int> Mask::random_location()
{
	int r = 0, c = 0;
	do {
		r = random(0, rows - 1);
		c = random(0, columns - 1);
		std::cout << "the location: " << r << ", " << c << std::endl;
	} while (!bits[r][c]);
	return std::make_pair(r, c);
}

