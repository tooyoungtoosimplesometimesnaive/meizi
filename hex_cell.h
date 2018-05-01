#ifndef HEX_CELL_H
#define HEX_CELL_H

#include <vector>
#include "cell.h"

class Hex_cell : public Cell
{
public:
	Hex_cell(int row, int column) : Cell(row, column) {}
	
	std::vector<Hex_cell*> neighbors();

	Hex_cell* northeast;
	Hex_cell* northwest;
	Hex_cell* southeast;
	Hex_cell* southwest;
	Hex_cell* north;
	Hex_cell* south;
};
#endif
