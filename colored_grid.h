#ifndef COLORED_GRID_H
#define COLORED_GRID_H

#include <opencv2/core.hpp>
#include "grid.h"
#include "cell.h"
#include "distances.h"

class Colored_grid: public Grid
{
public:
	Colored_grid(int r, int c) : Grid(r, c) {}
	cv::Scalar background_color_for(Cell cell);
	// Use this function to set the distances in this class
	void set_distances(Distances d);
private:
	Distances distances;
	Cell farthest;
	int maximum;
};
#endif
