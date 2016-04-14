#include "parallel_quad_tree.h"


QuadTree::QuadTree(unique_ptr<Bucket> && bucket) : ptr_bucket_(move(bucket)) {}

void QuadTree::Balance() {}

void QuadTree::AddSite(int id, int x, int y) {}

void QuadTree::MoveSite(int id, int x, int y) {}

void QuadTree::Split() {
	assert(ptr_bucket_.get() == nullptr);
	auto p0 = make_unique<QuadTree>(make_unique<Bucket>());
	auto p1 = make_unique<QuadTree>(make_unique<Bucket>());
	auto p2 = make_unique<QuadTree>(make_unique<Bucket>());
	auto p3 = make_unique<QuadTree>(make_unique<Bucket>());
	children[0] = move(p0);
	children[0] = move(p0);
	children[0] = move(p0);
	children[0] = move(p0);
}
