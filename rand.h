#ifndef RAND_H
#define RAND_H

#include <random>

static std::random_device rd;
static std::mt19937 gen(rd());

static int random(int s, int e)
{
	std::uniform_int_distribution<int> dist(s, e);
	return dist(gen);
}

#endif
