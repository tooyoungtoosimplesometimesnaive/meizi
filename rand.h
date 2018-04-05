#ifndef RAND_H
#define RAND_H

#include <random>

std::random_device rd;
std::mt19937 gen(rd());

int random(int s, int e)
{
	std::uniform_int_distribution<int> dist(s, e);
	return dist(gen);
}

#endif
