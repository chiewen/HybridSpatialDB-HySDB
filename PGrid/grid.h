#pragma once

#include <array> 
#include <boost/serialization/singleton.hpp>
#include "bucket.h"
#include <mutex>
#include <vector>
#include <memory>
#include <atomic>

using namespace std;
using boost::serialization::singleton;

const static int kGridWidth = 1 << 8;
const static float kSpaceWidth = 1 << 17;
const static int kSpacePerCellBitwise = 9;

static mutex g_mutex[kGridWidth][kGridWidth];
static atomic<unsigned> g_reader[kGridWidth][kGridWidth];

class Grid : public singleton<Grid> {
public:
	FRIEND_TEST(Container, Grid);
	Grid();
	void Clear();
	void AddSite(int id, int x, int y);
	void DelSite(int id);
	void MoveSite(int id, int x, int y);

	static void Query(vector<SiteValue>& result, int x1, int y1, int x2, int y2, int tq);
private:
	unique_ptr<Bucket> grid[kGridWidth][kGridWidth];

	static int get_coordinate(int cord);
	pair<Bucket*, unsigned> AddToCell(int id, int x, int y, int col, int row);
	bool RemoveFromCell(int id, int col, int row);
	static void RetrieveAllSitesInCell(vector<SiteValue>& result, int col, int row);
	static void RetrieveSitesInCell(vector<SiteValue>& result, int col, int row, int x1, int y1, int x2, int y2, int tq);

};


inline int Grid::get_coordinate(int cord) {
	return cord >> kSpacePerCellBitwise;
}

