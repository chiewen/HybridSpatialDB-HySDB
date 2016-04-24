#pragma once

#include <array>
#include "gtest/gtest_prod.h"
#include "site.h"
#include <memory>

using namespace std;

class Bucket {
	FRIEND_TEST(Container, Grid);
	FRIEND_TEST(Container, Bucket);
	FRIEND_TEST(ParallelMOD, QuadTree);

	friend class Grid;
	friend class QuadTree;

	static const int kSize = 32;
	array<Site, kSize> sites_;
	unsigned current_ = 0;
	unsigned readers_ = 0;
	unique_ptr<Bucket> next_ = nullptr;

public:
	bool is_full() const;
	bool is_empty() const;

	void* operator new(size_t size){ return _aligned_malloc(size, 16); };
	void operator delete(void * ptr) { _aligned_free(ptr); };

	pair<Bucket*, unsigned> Add(int id, int x, int y);
	tuple<int, Bucket*, unsigned, bool, bool> Del(const int id);
};


inline bool Bucket::is_full() const {
	return current_ == kSize;
}

inline bool Bucket::is_empty() const {
	return current_ == 0;
}

