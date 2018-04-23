#ifndef HEX_CELL_H
#define HEX_CELL_H

#include <vector>
#include "cell.h"

class Hex_cell : public Cell
{
public:
	Hex_cell(int row, int column) : Cell(row, column) {}
	
	std::vector<Hex_cell*> neighbors();
};
#endif
