#include "grid.h"
#include "maze_algorithms/recursive_back_tracker.h"

int main()
{
	/*
	Polar_grid g(8, 8);
	recursive_back_tracker rb;
	rb.on(g);

	g.to_img(20, "polar_test.png");
	*/

	Polar_grid g(8);
	recursive_back_tracker<Polar_grid> rb;
	rb.on(g);
	g.to_img(20, "polar_test_2.png");

	Polar_grid g2(16);
	g2.to_img(20, "polar_test_3.png");

	return 0;
}
	
