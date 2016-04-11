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
	Bucket* next_ = nullptr;

public:
	~Bucket() {
		next_->~Bucket();
		_aligned_free(next_);
	}
	bool is_full() const;
	bool is_empty() const;

	void init() {
		current_ = 0;
		readers_ = 0;
		next_ = nullptr;
	}

	pair<Bucket*, unsigned> Add(int id, int x, int y, int col, int row);
	tuple<int, Bucket*, unsigned, bool, bool> Del(const int id);
};


inline bool Bucket::is_full() const {
	return current_ == kSize;
}

inline bool Bucket::is_empty() const {
	return current_ == 0;
}

