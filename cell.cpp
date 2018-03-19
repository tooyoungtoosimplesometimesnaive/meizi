#include <vector>
#include  "cell.h"


void Cell::link(Cell& c, bool bidirectionally = true)
{
	links.insert(c);
	if (bidirectionally)
	{
		c.link(this, false);
	}
}


void Cell::unlink(Cell& c, bool bidirectionally = true)
{
	links.erase(c);
	if (bidirectionally)
	{
		c.unlink(this, false);
	}
}


// linked?
bool is_linked(Cell& c)
{
	return links.find(c) != links.end();
}

// get the neighbors
std::vector<Cell> neighbors()
{
	std::vector<cell> v({});
	if (north)
		v.push_back(north);
	if (south)
		v.push_back(south);
	if (east)
		v.push_back(east);
	if (west)
		v.push_back(west);
	return v;
}

