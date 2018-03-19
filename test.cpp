
#include <iostream>
#include "grid.h"
#include "cell.h"
#include "binary_tree.h"

using namespace std;

int main()
{
	binary_tree b;
	Grid g(4, 4);
	b.on(g);

	return 0;
}
