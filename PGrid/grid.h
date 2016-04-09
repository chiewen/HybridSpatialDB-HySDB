#pragma once

#include <array> 
#include <boost/serialization/singleton.hpp>
#include "bucket.h"
#include <mutex>
#include <vector>

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
	FRIEND_TEST(Container, Grid);
	Grid();
	void Clear();
	void AddSite(int id, float x, float y);
	void DelSite(int id);
	void MoveSite(int id, float x, float y);

	static void Query(vector<Site> &result, float x1, float y1, float x2, float y2, long int tq);
private:
	static int get_coordinate(float cord);
	pair<Bucket*, unsigned> AddToCell(int id, float x, float y, int col, int row);
	bool RemoveFromCell(int id, int col, int row);
	static void RetrieveAllSitesInCell(vector<Site> &result, int col, int row);
	static void RetrieveSitesInCell(vector<Site> &result, int col, int row, float x1, float y1, float x2, float y2, long int tq);

};


inline int Grid::get_coordinate(float cord) {
	return static_cast<int>(cord) >> kSpacePerCellBitwise;
}

