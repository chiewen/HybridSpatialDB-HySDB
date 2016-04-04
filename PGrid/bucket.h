#pragma once
#include <memory> 
#include <array>
#include "site.h"

using namespace std;

class Bucket {
public:
	static const int kSize = 32;
	array<Site, kSize> sites_;
	unsigned current_ = 0;
	unique_ptr<Bucket> next_ = nullptr;

	bool is_full() const;
	bool is_empty() const;

	pair<Bucket*, unsigned> Add(const Site& site, int row, int col);
	void Del(const int id);
};


inline bool Bucket::is_full() const {
	return current_ == kSize;
}

inline bool Bucket::is_empty() const {
	return current_ == 0;
}

