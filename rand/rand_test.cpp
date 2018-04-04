#include <iostream>
#include <vector>
#include <random>

std::random_device rd;
std::mt19937 gen(rd());

void do_dist(int s, int e)
{
	std::uniform_int_distribution<int> dist(s, e);
	std::vector<int> v (e + 1, 0);
	for (int i = 0; i < 100000; i++)
	{
		v[dist(gen)] ++;
	}
	for (int j = s; j <= e; j++)
	{
		std::cout << j << " : " << v[j] << std::endl;
	}
}

int main()
{
	do_dist(1, 10);
	std::cout << "------" << std::endl;
	do_dist(1, 5);
	std::cout << "------" << std::endl;
	do_dist(5, 15);

	return 0;
}

