#include "grid.h"
#include "maze_algorithms/recursive_back_tracker.h"

int main()
{
	Triangle_grid g(10, 17);
	recursive_back_tracker<Triangle_grid> rb;
	rb.on(g);
	g.to_img(20, "triangle_grid.png");

	return 0;
}
