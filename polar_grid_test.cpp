#include "polar_grid.h"
#include "recursive_back_tracker.h"

int main()
{
	Polar_grid g(8, 8);
	recursive_back_tracker rb;
	rb.on(g);

	g.to_img(20, "polar_test.png");
	return 0;
}
	
