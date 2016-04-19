#include "parallel_quad_tree.h"
#include "index.h"


QuadTree::QuadTree(unique_ptr<Bucket>&& bucket, int left, int right, int floor, int ceiling) :
	ptr_bucket_(move(bucket)), left(left), right(right), floor(floor), ceiling(ceiling),
	x_middle((left + right)/2), y_middle((floor+ceiling)/2) {}

void QuadTree::Balance() {
	
}

void QuadTree::AddSite(int id, int x, int y) {
	auto added = AddToLeaf(id, x, y);
	auto& si = Index::get_mutable_instance();
	assert(si.find(id) == si.end());
	si.emplace(make_pair(id, Element(added.first, added.second)));
}

pair<Bucket*, unsigned> QuadTree::AddToLeaf(int id, int x, int y) {
	if (IsLeaf()) {
		if (ptr_bucket_->is_full()) {
			auto new_bucket = make_unique<Bucket>();
			new_bucket->next_ = move(ptr_bucket_);
			ptr_bucket_ = move(new_bucket);
		}
		return ptr_bucket_->Add(id, x, y);
	}
	else {
		if (x >= x_middle) {
			if (y >= y_middle) return children[0]->AddToLeaf(id, x, y);
			else return children[3]->AddToLeaf(id, x, y);
		}
		else {
			if (y >= y_middle) return children[1]->AddToLeaf(id, x, y);
			else return children[2]->AddToLeaf(id, x, y);
		}
	}
}

void QuadTree::MoveSite(int id, int x, int y, int x_new, int y_new) {
	
}

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

