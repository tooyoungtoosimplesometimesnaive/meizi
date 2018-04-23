#include "hex_cell.h"
#include <vector>


std::vector<Hex_cell*> Hex_cell::neighbors()
{
	std::vector<Hex_cell*> l({});
	if (northwest) {
		l.push_back(northwest);
	}
	if (north) {
		l.push_back(north);
	}
	if (northeast) {
		l.push_back(northeast);
	}
	if (southwest) {
		l.push_back(southwest);
	}
	if (south) {
		l.push_back(south);
	}
	if (southeast) {
		l.push_back(southeast);
	}
	return l;
}
