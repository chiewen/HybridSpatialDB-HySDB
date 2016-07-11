#pragma once

#include "gtest/gtest_prod.h"

class LfGrid;

class LfBucket {
	FRIEND_TEST(LockFreeGrid, Bucket);
	friend class LfGrid;

public:
	LfBucket();
	~LfBucket();
};

