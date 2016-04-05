#pragma once
#include <memory> 
#include <array>
#include "gtest/gtest_prod.h"
#include "site.h"

using namespace std;

class Bucket {
	FRIEND_TEST(Container, Grid);
	FRIEND_TEST(Container, Bucket);
	friend class Grid;

	static const int kSize = 32;
	array<Site, kSize> sites_;
	unsigned current_ = 0;
	unsigned readers_ = 0;
	unique_ptr<Bucket> next_ = nullptr;

public:
	bool is_full() const;
	bool is_empty() const;

	pair<Bucket*, unsigned> Add(int id, float x, float y, int row, int col);
	tuple<int, Bucket*, unsigned, bool> Del(const int id);
};


inline bool Bucket::is_full() const {
	return current_ == kSize;
}

inline bool Bucket::is_empty() const {
	return current_ == 0;
}

