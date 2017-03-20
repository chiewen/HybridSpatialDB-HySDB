#pragma once

#include <array> 
#include <boost/serialization/singleton.hpp>
#include "LfBucket.h"
#include <mutex>
#include <vector>
#include <memory>
#include <atomic>
#include <site_container.h>

using namespace std;
using boost::serialization::singleton;

const static int kGridWidth = 1 << 8;
const static float kSpaceWidth = 1 << 17;
const static int kSpacePerCellBitwise = 9;

class LfGrid : public SiteContainer, public singleton<LfGrid> {
public:
	FRIEND_TEST(LockFreeGrid, Bucket);

	LfGrid();

	static void Reset();

	//static void AddSite(int id, int x, int y);
	//static void DelSite(int id);
	static void MoveSite(int id, int x, int y);

	void Query(vector<SiteValue>& result, int x1, int y1, int x2, int y2, int tq) override;

private:
	static unique_ptr<LfBucket> grid[kGridWidth][kGridWidth];

	static int get_coordinate(int cord);

	void MoveToCell(int id, int x, int y, int col, int row);
	//static bool RemoveFromCell(int id, int col, int row);

	static void RetrieveAllSitesInCell(vector<SiteValue>& result, int col, int row);
	static void RetrieveSitesInCell(vector<SiteValue>& result, int col, int row, int x1, int y1, int x2, int y2, int tq);

};


inline LfGrid::LfGrid() {
	Reset();
}

inline int LfGrid::get_coordinate(int cord) {
	return cord >> kSpacePerCellBitwise;
}

