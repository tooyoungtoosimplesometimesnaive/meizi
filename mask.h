#ifndef MASK_H
#define MASK_H

#include <string>
#include <vector>
#include <utility>

class Mask
{
public:
	Mask(int r, int c);
	Mask(std::string filename);

	bool at(int row, int column);
	void put(int row, int column, bool value);
	int count();
	std::pair<int, int> random_location();

	int rows, columns;
	std::vector<std::vector<bool>> bits;
};

#endif
