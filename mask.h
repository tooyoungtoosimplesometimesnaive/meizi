#ifndef MASK_H
#define MASK_H

#include <vector>

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
	int rows, columns;
	std::vector<std::vector<bool>> bits;
}
