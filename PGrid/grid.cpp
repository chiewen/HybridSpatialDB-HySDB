#include "grid.h"
#include "secondary_index.h"

Grid::Grid() {
	RefillEmpty();
}

void Grid::RefillEmpty() {
	for (auto& bucket_array : *this)
		for (auto& bucket : bucket_array)
			bucket = make_unique<Bucket>();
}

void Grid::RefreshSecondaryIndex(const int id, Bucket* bucket, unsigned index, int row, int col) {
	auto& si = SecondaryIndex::get_mutable_instance();
	auto p = si.find(id);

	if (p == si.end())
		si.emplace(make_pair(id, SecondaryElement(bucket, index, row, col)));
	else
		p->second.RefreshValues(bucket, index, row, col);
}

void Grid::AddSite(const Site& site, int row, int col) {
	if ((*this)[row][col]->is_full()) {
		auto new_bucket = make_unique<Bucket>();
		new_bucket->next_ = move((*this)[row][col]);
		(*this)[row][col] = move(new_bucket);
	}

	auto added = (*this)[row][col]->Add(site, row, col);
	RefreshSecondaryIndex(site.id, added.first, added.second, row, col);
}

void Grid::DelSite(const Site& site) {
	int row = get_coordinate(site.y);
	int col = get_coordinate(site.x);

	(*this)[row][col]->Del(site.id);

	if ((*this)[row][col]->is_empty()) {
		auto temp_ptr = move((*this)[row][col]->next_);
		(*this)[row][col] = move(temp_ptr);
	}
}

void Grid::MoveSite(const Site& site) {
	int row = get_coordinate(site.y);
	int col = get_coordinate(site.x);

	auto ptr = SecondaryIndex::GetById(site.id);
	if (!ptr) {
		AddSite(site,row, col);
		return;
	}

	if (ptr->col == col && ptr->row == row) {// local update
		auto p_site = ptr->p_bucket->sites_.begin() + ptr->index;
		p_site->x = site.x;
		p_site->y = site.y;
		p_site->tu = chrono::high_resolution_clock::now();
	}
	else {// non-local update
		
	}
}
