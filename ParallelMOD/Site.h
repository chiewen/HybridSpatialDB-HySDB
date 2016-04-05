#pragma once
#include <string>
#include <ctime>

using namespace std;

struct Site {
	int id;
	float x;
	float y;
	long int tu;

	Site() = default;

	Site(int id, float x, float y)
		: id(id), x(x), y(y), tu(static_cast<long int>(time(nullptr))) { }
};

