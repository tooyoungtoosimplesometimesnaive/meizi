#ifndef CELL_HASH_H
#define CELL_HASH_H

#include <string>
#include "cell.h"

struct Cell_hash
{
	std::size_t operator()(const Cell& c) const
	{
		std::string h = std::to_string(c.row) + " " + std::to_string(c.column);
		return std::hash<std::string>()(h);
	}
};

#endif
