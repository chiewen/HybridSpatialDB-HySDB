#include "parallel_quad_tree.h"


QuadTree::QuadTree(unique_ptr<Bucket>&& bucket, int left, int right, int floor, int ceiling) :
	ptr_bucket_(move(bucket)), left(left), right(right), floor(floor), ceiling(ceiling),
	x_middle((left + right)/2), y_middle((floor+ceiling)/2) {}

void QuadTree::Balance() {}

void QuadTree::AddSite(int id, int x, int y) {}

void QuadTree::MoveSite(int id, int x, int y) {}

void QuadTree::Split() {
	auto p0 = make_unique<QuadTree>(make_unique<Bucket>(), x_middle, right, y_middle, ceiling);
	auto p1 = make_unique<QuadTree>(make_unique<Bucket>(), left, x_middle, y_middle, ceiling);
	auto p2 = make_unique<QuadTree>(make_unique<Bucket>(), left, x_middle, floor, y_middle);
	auto p3 = make_unique<QuadTree>(make_unique<Bucket>(), x_middle, right, floor, y_middle);
	children[0] = move(p0);
	children[1] = move(p1);
	children[2] = move(p2);
	children[3] = move(p3);
}

