#pragma once
#include <string>
#include <ctime>
#include <mutex>

using namespace std;

const static int kMaxSiteNum = 1 << 16;

static mutex s_mutex[kMaxSiteNum];

struct Site {
	int id;
	float x;
	float y;
	long int tu;

	Site() = default;

	Site(int id, float x, float y)
		: id(id), x(x), y(y), tu(static_cast<long int>(time(nullptr))) { }
};

