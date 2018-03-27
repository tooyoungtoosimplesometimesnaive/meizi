#ifndef DISTANCE_GRID_H
#define DISTANCE_GRID_H

#include <string>
#include <sstream>
#include "cell.h"
#include "distances.h"
#include "grid.h"

/*
 * For displaying purpose, showing the int in a form of base-36:
 * i.e. 10 will be a, and z will be 35
 */
std::string transform_int(int i)
{
	if (i < 10 || i > 35) {
		std::stringstream ss;
		ss << i;
		std::string d;
		ss >> d;
		return d;
	} else {
		char a = 'a' + (i - 10);
		std::stringstream ss;
		ss << a;
		std::string d;
		ss >> d;
		return d;
	}
}

class Distance_grid: public Grid
{
public:
	Distance_grid(int r, int c) : Grid(r, c)
	{
	}
	std::string contents_of(Cell cell)
	{
		if (distances.cells.find(cell) != distances.cells.end())
		{
			int di = distances.cells[cell];
			return transform_int(di);
		}
		else {
			return " ";
		}
	};

	Distances distances;
};

#endif
