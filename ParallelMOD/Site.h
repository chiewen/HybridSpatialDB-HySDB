#pragma once
#include <string>
#include <chrono>

using namespace std;

struct Site {
	int id;
	float x;
	float y;
	chrono::high_resolution_clock::time_point tu;

	Site() = default;

	Site(int id, float x, float y)
		: id(id), x(x), y(y), tu(chrono::high_resolution_clock::now()) { }
};

