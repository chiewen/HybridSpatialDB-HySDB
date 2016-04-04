#pragma once

#include <array> 
#include <boost/serialization/singleton.hpp>
#include "bucket.h"

using namespace std;
using boost::serialization::singleton;

const static int kGridWidth = 1 << 8;
const static float kSpaceWidth = 1 << 17;
const static int kSpacePerCellBitwise = 9;

class Grid : public array<array<unique_ptr<Bucket>, kGridWidth>, kGridWidth>, public singleton<Grid> {
public:
	Grid();
	void RefillEmpty();

	static int get_coordinate(float cord);
	static void RefreshSecondaryIndex(const int id, Bucket* bucket, unsigned index, int row, int col);

	void AddSite(const Site& site, int row, int col);
	void DelSite(const Site& site);
	void MoveSite(const Site& site);
};


inline int Grid::get_coordinate(float cord) {
	return static_cast<int>(cord) >> kSpacePerCellBitwise;
}