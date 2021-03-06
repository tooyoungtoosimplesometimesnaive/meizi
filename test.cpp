
#include <iostream>
#include "grid.h"
#include "cell.h"
#include "maze_algorithms/binary_tree.h"
#include "maze_algorithms/sidewinder.h"
#include "maze_algorithms/aldous_broder.h"
#include "maze_algorithms/wilsons.h"
#include "maze_algorithms/hunt_and_kill.h"
#include "maze_algorithms/recursive_back_tracker.h"

using namespace std;

int main()
{
	binary_tree b;
	Grid g(4, 4);
	b.on(g);

	cout << g << endl;
	cout << g.deadends().size() << " deadends." << endl;

	cout << endl;

	Grid g2(8, 8);
	sidewinder s;
	s.on(g2);

	cout << g2 << endl;
	cout << g2.deadends().size() << " deadends." << endl;
	g2.to_svg(40, "rectangular_grid.html");

	Grid g3(8, 8);
	aldous_broder<Grid> ab;
	ab.on(g3);

	cout << g3 << endl;
	cout << g3.deadends().size() << " deadends." << endl;

	Grid g4(8, 8);
	wilsons w;
	w.on(g4);

	cout << g4 << endl;
	cout << g4.deadends().size() << " deadends." << endl;

	Grid g5(8, 8);
	hunt_and_kill hk;
	hk.on(g5);

	cout << g5 << endl;
	cout << g5.deadends().size() << " deadends." << endl;

	Grid g6(8, 8);
	recursive_back_tracker<Grid> rbt;
	rbt.on(g6);

	cout << g6 << endl;
	cout << g6.deadends().size() << " deadends." << endl;
	return 0;
}
