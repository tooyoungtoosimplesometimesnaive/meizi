#include <algorithm>
#include <vector>
#include  "cell.h"


bool operator==(Cell& lhs, Cell& rhs)
{
	return lhs.row == rhs.row && lhs.column && rhs.column;
}

void Cell::link(Cell* c, bool bidirectionally)
{
	if (std::find(links.begin(), links.end(), c) == links.end())
		links.push_back(c);

	if (bidirectionally)
	{
		c->link(this, false);
	}
}


void Cell::unlink(Cell* c, bool bidirectionally)
{
	auto it = std::find(links.begin(), links.end(), c);
	links.erase(it);

	if (bidirectionally)
	{
		c->unlink(this, false);
	}
}


// linked?
bool Cell::is_linked(const Cell* c) const
{
	auto it = std::find(links.begin(), links.end(), c);
	return it != links.end();
}

// get the neighbors
std::vector<Cell*> Cell::neighbors()
{
	std::vector<Cell*> v({});
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

