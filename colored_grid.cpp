#include <opencv2/core.hpp>
#include "colored_grid.h"
#include "cell.h"

#include <iostream>
cv::Scalar Colored_grid::background_color_for(Cell cell)
{
	int dist = distances.cells[cell];
	double intensity = ((double)maximum - dist) / (double) maximum;
	double dark = (255 * intensity);
	double bright = 128 + 127 * intensity;
	std::cout << dark << " " << bright << std::endl;
	return cv::Scalar(dark, bright, dark);
}

void Colored_grid::set_distances(Distances d)
{
	distances = d;
	auto p = d.max_distance();
	farthest = p.first;
	maximum = p.second;
}
