#ifndef MASK_H
#define MASK_H

#include <vector>
#include <utility>

class Mask
{
public:
	Mask(int r, int c) : rows(r), columns(c), bits({}) {
		for (int i = 0; i < r; i++)
		{
			std::vector<bool> r(c, false);
			bits.push_back(r);
		}
	}

	bool at(int row, int column);
	int count();
	std::pair<int, int> random_loaction();

	int rows, columns;
	std::vector<std::vector<bool>> bits;
}
