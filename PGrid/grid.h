#pragma once

#include <array> 
#include <boost/serialization/singleton.hpp>
#include "bucket.h"
#include <mutex>

using namespace std;
using boost::serialization::singleton;

const static int kGridWidth = 1 << 8;
const static float kSpaceWidth = 1 << 17;
const static int kSpacePerCellBitwise = 9;

static mutex g_mutex[kGridWidth][kGridWidth];
static unsigned g_reader[kGridWidth][kGridWidth];

class Grid : public array<array<unique_ptr<Bucket>, kGridWidth>, kGridWidth>,
             public singleton<Grid> {
public:
	Grid();
	void Clear();
	void AddSite(int id, float x, float y, int row, int col);
	void DelSite(int id);
	void MoveSite(int id, float x, float y);
private:
	static int get_coordinate(float cord);
	pair<Bucket*, unsigned> AddToCell(int id, float x, float y, int row, int col);
	void RemoveFromCell(int id, int row, int col);
};


inline int Grid::get_coordinate(float cord) {
	return static_cast<int>(cord) >> kSpacePerCellBitwise;
}

