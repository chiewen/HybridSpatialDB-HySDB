#pragma once

#include <array>
#include <memory>
#include "gtest/gtest_prod.h"
#include "bucket.h"
#include <assert.h>
#include <iostream>

using namespace std;

class QuadTree {
	FRIEND_TEST(ParallelMOD, QuadTree);

	static const int LEFT = 0;
	static const int RIGHT = 20000;
	static const int FLOOR = 0;
	static const int CEILING = 20000;

	array<unique_ptr<QuadTree>, 4> children;
	unique_ptr<Bucket> ptr_bucket_ = nullptr;
	mutex mutex_;

	int left;
	int right;
	int floor;
	int ceiling;
	int x_middle;
	int y_middle;

public:
	QuadTree() = delete;
	QuadTree(unique_ptr<Bucket>&& bucket, int left, int right, int floor, int ceiling);

	static QuadTree root_tree_;

	void* operator new(size_t size) {
		return _aligned_malloc(size, 16);
	};

	void operator delete(void* ptr) {
		_aligned_free(ptr);
	};

	inline bool IsLeaf() const;
	void Balance();
	void AddSite(int id, int x, int y);
	QuadTree* GetLeaf(int x, int y);
	pair<Bucket*, unsigned> AddToLeaf(int id, int x, int y);
	bool RemoveSite(int id, Bucket* const bucket, const unsigned index);
	static void MoveSite(int id, int x, int y, int x_new, int y_new);
	void Split();
};

bool QuadTree::IsLeaf() const {
	assert(all_of(children.begin(), children.end(), [](const unique_ptr<QuadTree>& p) {
		return p.get() == nullptr;
	}) == any_of(children.begin(), children.end(), [](const unique_ptr<QuadTree>& p) {
		return p.get() == nullptr;
	}));

	return children[0].get() == nullptr;
}

