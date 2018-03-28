
#include <iostream>
#include "colored_grid.h"
#include "cell.h"
#include "binary_tree.h"

using namespace std;

int main()
{
	binary_tree b;
	Colored_grid g(10, 10);
	b.on(g);

	auto start = g.at(g.rows / 2, g.columns / 2);
	g.set_distances(start->distances());


	cout << g << endl;

	g.to_img(40, "colorized.png");

	return 0;
}
