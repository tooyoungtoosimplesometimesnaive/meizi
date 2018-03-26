#ifndef CELL_HASH_H
#define CELL_HASH_H

#include <string>
#include <sstream>
#include "cell.h"

struct Cell_hash
{
	std::size_t operator()(const Cell& c) const
	{
		std::stringstream s_c_r, s_c_c;
		std::string c_r, c_c;
		s_c_r << c.row;
		s_c_c << c.column;
		s_c_r >> c_r;
		s_c_c >> c_c;
		return std::hash<std::string>()(c_r + " " + c_c);
	}
};

#endif
