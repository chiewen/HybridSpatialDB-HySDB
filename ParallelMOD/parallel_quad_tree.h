#pragma once

#include <array>
#include <memory>
#include "gtest/gtest_prod.h"
#include "bucket.h"
#include <assert.h>

using namespace std;

class QuadTree {
	FRIEND_TEST(ParallelMOD, QuadTree);
	array<unique_ptr<QuadTree>, 4> children;
	unique_ptr<Bucket> ptr_bucket_ = nullptr;

public:
	QuadTree() = delete;
	QuadTree(unique_ptr<Bucket>&& bucket);
	inline bool IsLeaf() const;
	void Balance();
	void AddSite(int id, int x, int y);
	void MoveSite(int id, int x, int y);
	void Split();
};

bool QuadTree::IsLeaf() const {
	assert( all_of(children.begin(), children.end(), [](const unique_ptr<QuadTree>& p) {
		return p.get() == nullptr;
	}) == any_of(children.begin(), children.end(), [](const unique_ptr<QuadTree>& p) {
		return p.get() == nullptr;
	}) == (ptr_bucket_.get() != nullptr));

	return ptr_bucket_.get() != nullptr;
}

