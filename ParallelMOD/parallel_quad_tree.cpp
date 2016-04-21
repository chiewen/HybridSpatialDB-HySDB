#include "parallel_quad_tree.h"
#include "index.h"

QuadTree QuadTree::root_tree_{make_unique<Bucket>(), LEFT, RIGHT, FLOOR, CEILING};

QuadTree::QuadTree(unique_ptr<Bucket>&& bucket, int left, int right, int floor, int ceiling) :
	children{}, ptr_bucket_{move(bucket)}, left(left), right(right), floor(floor), ceiling(ceiling),
	x_middle((left + right) / 2), y_middle((floor + ceiling) / 2) {}

//TODO call cuda code
void QuadTree::Balance() {}

void QuadTree::AddSite(int id, int x, int y) {
	auto added = AddToLeaf(id, x, y);
	auto& si = Index::get_mutable_instance();
	assert(si.find(id) == si.end());
	si.emplace(make_pair(id, Element(added.first, added.second)));
}

QuadTree* QuadTree::GetLeaf(int x, int y) {
	if (IsLeaf())
		return this;
	else {
		if (x >= x_middle) {
			if (y >= y_middle) return children[0]->GetLeaf(x, y);
			else return children[3]->GetLeaf(x, y);
		}
		else {
			if (y >= y_middle) return children[1]->GetLeaf(x, y);
			else return children[2]->GetLeaf(x, y);
		}
	}
}

pair<Bucket*, unsigned> QuadTree::AddToLeaf(int id, int x, int y) {
	auto p_quad_tree = GetLeaf(x, y);

	if (p_quad_tree->ptr_bucket_->is_full()) {
		auto new_bucket = make_unique<Bucket>();
		new_bucket->next_ = move(p_quad_tree->ptr_bucket_);
		p_quad_tree->ptr_bucket_ = move(new_bucket);
	}
	return p_quad_tree->ptr_bucket_->Add(id, x, y);
}

bool QuadTree::RemoveSite(int id, Bucket* const bucket, const unsigned index) {
	lock_guard<mutex> {mutex_};

	//LATER count current reader
	//while (g_reader[col][row] > 0);

	auto swapped = ptr_bucket_->Del(id);
	if (get<4>(swapped) == false) return false;
	if (get<0>(swapped) >= 0) {
		Index::get_mutable_instance().RenewSwappedSite(
			get<0>(swapped), get<1>(swapped), get<2>(swapped));

		if (ptr_bucket_->is_empty()) {
			auto temp_ptr = move(ptr_bucket_->next_);
			ptr_bucket_ = move(temp_ptr);
		}
	}
	return true;
}

void QuadTree::MoveSite(int id, int x, int y, int x_new, int y_new) {
	auto& element = Index::get_mutable_instance().find(id)->second;
	auto p_old = root_tree_.GetLeaf(x, y);
	auto p_new = root_tree_.GetLeaf(x_new, y_new);

	//LATER concurrency control
	if (p_new == p_old) {
		element.p_bucket->sites_[element.index].SetValue(id, x, y, static_cast<int>(time(nullptr)));
	}
	else {
		auto added = p_new->AddToLeaf(id, x_new, y_new);
		p_old->RemoveSite(id, element.p_bucket, element.index);
		element.p_bucket = added.first;
		element.index = added.second;
	}
}

void QuadTree::Split() {
	//LATER concurrency control
	auto p0 = make_unique<QuadTree>(make_unique<Bucket>(), x_middle, right, y_middle, ceiling);
	auto p1 = make_unique<QuadTree>(make_unique<Bucket>(), left, x_middle, y_middle, ceiling);
	auto p2 = make_unique<QuadTree>(make_unique<Bucket>(), left, x_middle, floor, y_middle);
	auto p3 = make_unique<QuadTree>(make_unique<Bucket>(), x_middle, right, floor, y_middle);
	children[0] = move(p0);
	children[1] = move(p1);
	children[2] = move(p2);
	children[3] = move(p3);
}

