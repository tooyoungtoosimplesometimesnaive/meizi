#include <iostream>
#include "distances.h"
#include "cell.h"
#include "grid.h"
#include "distance_grid.h"
#include "maze_algorithms/binary_tree.h"

int main()
{
	Distance_grid grid(5, 5);
	binary_tree b;
	b.on(grid);
	Cell* start = grid.at(0, 0);
	Distances distances = start->distances();
	grid.distances = distances;

	// grid.distances = grid.distances.root.distances();
	std::cout << grid << std::endl;

	// Get the distance from (0,0) to (row - 1, 0)
	grid.distances = distances.path_to(*grid.at(grid.rows - 1, 0));
	std::cout << grid << std::endl;
	
	/**
	 * Now test the longest path:
	 */
	Distance_grid grid2(5, 5);
	binary_tree b2;
	b2.on(grid2);
	Cell* start2 = grid2.at(0, 0);
	Distances distances2 = start2->distances();
	auto p = distances2.max_distance();
	Distances new_distances2 = p.first.distances();
	auto p2 = new_distances2.max_distance();
	grid2.distances = new_distances2.path_to(p2.first);

	std::cout << grid2 << std::endl;

	return 0;
}
