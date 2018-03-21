
#include <iostream>
#include "grid.h"
#include "cell.h"
#include "binary_tree.h"
#include "sidewinder.h"

using namespace std;

int main()
{
	binary_tree b;
	Grid g(4, 4);
	b.on(g);

	cout << g << endl;

	cout << endl;

	Grid g2(8, 8);
	sidewinder s;
	s.on(g2);

	cout << g2 << endl;
	g2.to_img(40);

	return 0;
}
