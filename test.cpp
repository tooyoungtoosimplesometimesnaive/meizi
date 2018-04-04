
#include <iostream>
#include "grid.h"
#include "cell.h"
#include "binary_tree.h"
#include "sidewinder.h"
#include "aldous_broder.h"
#include "wilsons.h"
#include "hunt_and_kill.h"

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
	// g2.to_img(40);

	Grid g3(8, 8);
	aldous_broder ab;
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
	return 0;
}
