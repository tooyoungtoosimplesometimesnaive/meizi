#include <iostream>
#include "cell.h"

int main()
{
	Cell s(0,0);
	Cell c(1,0);
	c.north = &s;
	std::cout << "OK" << std::endl;
	c.link(&s);
	std::cout << c.links.size() << std::endl;
	std::cout << s.links.size() << std::endl;
	c.unlink(&s);

	std::cout << c.links.size() << std::endl;
	std::cout << s.links.size() << std::endl;
	std::cout << c.north << std::endl;
	return 0;
}
