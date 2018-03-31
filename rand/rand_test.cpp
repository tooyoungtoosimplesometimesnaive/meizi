#include <iostream>
#include <vector>
#include <random>

std::random_device rd;
std::mt19937 gen(rd());

template <typename D>
void do_dist(D dist, int s, int e)
{
	std::vector<int> v (e - s + 2, 0);
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
	std::uniform_int_distribution<int> dist(1, 10);
	do_dist(dist, 1, 10);

	return 0;
}

