#ifndef POLAR_GRID_H
#define POLAR_GRID_H

#include "grid.h"

class Polar_grid : public Grid
{
public:
	Polar_grid(int r, int c) : Grid(r, c) {};
	void to_img(int cell_size = 10, std::string file_name = "maze.png");

};
#endif
