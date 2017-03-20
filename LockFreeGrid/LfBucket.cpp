#include "LfBucket.h"
#include <assert.h>

LfBucket::LfBucket() {}

LfBucket::~LfBucket() {}

void LfBucket::Add(int id, int x, int y) {
	assert(current_ < kSize);
	sites_[current_++].SetValue(id, x, y, static_cast<int>(time(nullptr)));
}
