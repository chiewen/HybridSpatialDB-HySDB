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

//void Grid::RefreshSecondaryIndex(const int id, Bucket* bucket, unsigned index, int row, int col) {
//	auto& si = SecondaryIndex::get_mutable_instance();
//	auto p = si.find(id);
//	assert(p != si.end());
//	p->second.RollInValues(bucket, index, row, col);
//}

//void Grid::AddSecondaryIndex(const int id, Bucket* bucket, unsigned index, int row, int col) {
//	auto& si = SecondaryIndex::get_mutable_instance();
//	assert(si.find(id) == si.end());
//	si.emplace(make_pair(id, SecondaryElement(bucket, index, row, col)));
//}

pair<Bucket*, unsigned> Grid::AddToCell(const Site& site, int row, int col) {
	if ((*this)[row][col]->is_full()) {
		auto new_bucket = make_unique<Bucket>();
		new_bucket->next_ = move((*this)[row][col]);
		(*this)[row][col] = move(new_bucket);
	}

	return (*this)[row][col]->Add(site, row, col);
}

//void Grid::AddSiteToNewCell(const Site& site, int row, int col) {
//	auto added = AddToCell(site, row, col);
//	RefreshSecondaryIndex(site.id, added.first, added.second, row, col);
//}

void Grid::AddNewSite(const Site& site, int row, int col) {
	auto added = AddToCell(site, row, col);
	auto& si = SecondaryIndex::get_mutable_instance();
	assert(si.find(site.id) == si.end());
	si.emplace(make_pair(site.id, SecondaryElement(added.first, added.second, row, col)));
}

void Grid::RemoveFromCell(const Site& site) {
	int row = get_coordinate(site.y);
	int col = get_coordinate(site.x);

	auto changed = (*this)[row][col]->Del(site.id);
	if (get<0>(changed) >= 0) {
		SecondaryIndex::get_mutable_instance().RenewPlaceChangedSite(
			get<0>(changed), get<1>(changed), get<2>(changed), get<3>(changed));

		if ((*this)[row][col]->is_empty()) {
			auto temp_ptr = move((*this)[row][col]->next_);
			(*this)[row][col] = move(temp_ptr);
		}
	}
}

void Grid::MoveSite(const Site& site) {
	int row = get_coordinate(site.y);
	int col = get_coordinate(site.x);

	auto ptr = SecondaryIndex::GetById(site.id);
	if (!ptr) {
		AddNewSite(site, row, col);
		return;
	}

	if (ptr->col == col && ptr->row == row) {// local update
		auto p_site = ptr->p_bucket->sites_.begin() + ptr->index;
		p_site->x = site.x;
		p_site->y = site.y;
		p_site->tu = static_cast<long int>(time(nullptr));
	}
	else {// non-local update

	}
}
