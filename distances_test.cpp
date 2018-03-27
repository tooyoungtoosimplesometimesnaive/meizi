#include <iostream>
#include "distances.h"
#include "cell.h"
#include "grid.h"
#include "distance_grid.h"
#include "binary_tree.h"

int main()
{
	Distance_grid grid(5, 5, 0, 0);
	binary_tree b;
	b.on(grid);
	Cell* start = grid.at(0, 0);
	Distances distances = start->distances();
	grid.distances = distances;

	// grid.distances = grid.distances.root.distances();
	std::cout << grid << std::endl;
	

	return 0;
}
