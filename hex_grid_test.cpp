#include "grid.h"
#include "maze_algorithms/recursive_back_tracker.h"

int main()
{
	Hex_grid g(10, 10);
	recursive_back_tracker<Hex_grid> rb;
	rb.on(g);
	g.to_img(20, "hex_grid.png");

	return 0;
}
