#include "grid.h"
#include "secondary_index.h"

Grid::Grid() {
	Clear();
}

void Grid::Clear() {
	for (auto& bucket_array : *this)
		for (auto& bucket : bucket_array)
			bucket = make_unique<Bucket>();
}

pair<Bucket*, unsigned> Grid::AddToCell(int id, float x, float y, int row, int col) {
	if ((*this)[row][col]->is_full()) {
		auto new_bucket = make_unique<Bucket>();
		new_bucket->next_ = move((*this)[row][col]);
		(*this)[row][col] = move(new_bucket);
	}

	return (*this)[row][col]->Add(id, x, y, row, col);
}

void Grid::AddSite(int id, float x, float y, int row, int col) {
	auto added = AddToCell(id, x, y, row, col);
	auto& si = SecondaryIndex::get_mutable_instance();
	assert(si.find(id) == si.end());
	si.emplace(make_pair(id, SecondaryElement(added.first, added.second, row, col)));
}

void Grid::DelSite(int id) {
	auto& si = SecondaryIndex::get_mutable_instance();
	auto p = si.find(id);
	if (p != si.end()) {
		RemoveFromCell(id, p->second.row, p->second.col);
		if (p->second.row_ld >= 0)
			RemoveFromCell(id, p->second.row_ld, p->second.col_ld);
	}
	si.erase(id);
}

void Grid::RemoveFromCell(int id, int row, int col) {
	auto swapped = (*this)[row][col]->Del(id);
	if (get<0>(swapped) >= 0) {
		SecondaryIndex::get_mutable_instance().RenewSwappedSite(
			get<0>(swapped), get<1>(swapped), get<2>(swapped), get<3>(swapped));

		if ((*this)[row][col]->is_empty()) {
			auto temp_ptr = move((*this)[row][col]->next_);
			(*this)[row][col] = move(temp_ptr);
		}
	}
}

void Grid::MoveSite(int id, float x, float y) {
	int row = get_coordinate(y);
	int col = get_coordinate(x);

	auto& si = SecondaryIndex::get_mutable_instance();
	auto p = si.find(id);
	if (p == si.end()) {
		AddSite(id, x, y, row, col);
		return;
	}

	auto ptr = &p->second;
	if (ptr->col == col && ptr->row == row) {// local update
		auto p_site = ptr->p_bucket->sites_.begin() + ptr->index;
		p_site->x = x;
		p_site->y = y;
		p_site->tu = static_cast<long int>(time(nullptr));
	}
	else {// non-local update
		if (ptr->row_ld >= 0)
			RemoveFromCell(id, ptr->row_ld, ptr->col_ld);
		auto added = AddToCell(id, x, y, row, col);
		ptr->p_bucket->sites_[ptr->index].tu = -ptr->p_bucket->sites_[ptr->index].tu;
		ptr->RollInValues(added.first, added.second, row, col);
	}
}

