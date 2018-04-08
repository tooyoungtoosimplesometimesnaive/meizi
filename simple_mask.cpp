#include <iostream>
#include "mask.h"
#include "masked_grid.h"
#include "recursive_back_tracker.h"

using namespace std;

int main()
{
	Mask mask(5, 5);
	mask.put(0, 0, false);
	mask.put(2, 2, false);
	mask.put(4, 4, false);

	Masked_grid grid(mask);
	recursive_back_tracker rb;
	rb.on(grid);

	cout << grid << endl;
	return 0;
}
