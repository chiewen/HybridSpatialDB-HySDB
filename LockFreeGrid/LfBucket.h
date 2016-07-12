#pragma once

#include <array>
#include "gtest/gtest_prod.h"
#include "site.h"
#include <memory>

using namespace std;

class LfGrid;

class LfBucket {
	FRIEND_TEST(LockFreeGrid, Bucket);
	friend class LfGrid;

public:
	LfBucket();
	~LfBucket();

	static const int kSize = 32;
	array<Site, kSize> sites_;
	unsigned current_ = 0;
	unique_ptr<LfBucket> next_ = nullptr;

public:
	bool is_full() const;
	bool is_empty() const;

	void* operator new(size_t size){ return _aligned_malloc(size, 16); };
	void operator delete(void * ptr) { _aligned_free(ptr); };

	void Add(int id, int x, int y);
	//tuple<int, LfBucket*, unsigned, bool, bool> Del(const int id);
};


inline bool LfBucket::is_full() const {
	return current_ == kSize;
}

inline bool LfBucket::is_empty() const {
	return current_ == 0;
}

