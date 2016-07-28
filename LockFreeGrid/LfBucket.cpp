#include "LfBucket.h"
#include <cassert>


LfBucket::LfBucket() {
}


LfBucket::~LfBucket() {
}

pair<LfBucket*, unsigned> LfBucket::Add(int id, int x, int y) {
	assert(current_ < kSize);
	sites_[current_].SetValue(id, x, y, static_cast<int>(time(nullptr)));

	return make_pair(this, current_++);
}

// use negative time stamp to indicate deleted object
void LfBucket::Del(int id, int x, int y) {
	assert(current_ < kSize);
	sites_[current_++].SetValue(id, x, y, -static_cast<int>(time(nullptr)));
}
