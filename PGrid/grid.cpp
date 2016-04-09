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

pair<Bucket*, unsigned> Grid::AddToCell(int id, float x, float y, int col, int row) {
	lock_guard<mutex>{g_mutex[col][row]};

	if ((*this)[col][row]->is_full()) {
		auto new_bucket = make_unique<Bucket>();
		new_bucket->next_ = move((*this)[col][row]);
		(*this)[col][row] = move(new_bucket);
	}

	return (*this)[col][row]->Add(id, x, y, col, row);
}

void Grid::AddSite(int id, float x, float y) {
	int col = get_coordinate(x);
	int row = get_coordinate(y);

	auto added = AddToCell(id, x, y, col, row);
	auto& si = SecondaryIndex::get_mutable_instance();
	assert(si.find(id) == si.end());
	si.emplace(make_pair(id, SecondaryElement(added.first, added.second, col, row)));
}

void Grid::DelSite(int id) {
	auto& si = SecondaryIndex::get_mutable_instance();
	auto p = si.find(id);
	if (p != si.end()) {
		// ReSharper disable once CppPossiblyErroneousEmptyStatements
		while (RemoveFromCell(id, p->second.col, p->second.row) == false);
		if (p->second.row_ld >= 0)
		// ReSharper disable once CppPossiblyErroneousEmptyStatements
			while (RemoveFromCell(id, p->second.col_ld, p->second.row_ld) == false);
	}
	si.erase(id);
}

bool Grid::RemoveFromCell(int id, int col, int row) {
	lock_guard<mutex>{g_mutex[col][row]};

	// ReSharper disable once CppPossiblyErroneousEmptyStatements
	while (g_reader[col][row] > 0);

	auto swapped = (*this)[col][row]->Del(id);
	if (get<4>(swapped) == false) return false;
	if (get<0>(swapped) >= 0) {
		SecondaryIndex::get_mutable_instance().RenewSwappedSite(
			get<0>(swapped), get<1>(swapped), get<2>(swapped), get<3>(swapped));

		if ((*this)[col][row]->is_empty()) {
			auto temp_ptr = move((*this)[col][row]->next_);
			(*this)[col][row] = move(temp_ptr);
		}
	}
	return true;
}

void Grid::RetrieveAllSitesInCell(vector<Site>& result, int col, int row) {
	auto p_bucket = get_mutable_instance()[col][row].get(); {
		lock_guard<mutex>{g_mutex[col][row]};
		g_reader[col][row] += 1;
		for (int i = p_bucket->current_ - 1; i >= 0; i--)
			result.emplace_back(p_bucket->sites_[i]);
	}
	p_bucket = p_bucket->next_.get();
	while (p_bucket) {
		for (int i = p_bucket->current_ - 1; i >= 0; i--)
			result.emplace_back(p_bucket->sites_[i]);
		p_bucket = p_bucket->next_.get();
	}

	g_reader[col][row] -= 1;
}

void Grid::RetrieveSitesInCell(vector<Site>& result, int col, int row,
                               float x1, float y1, float x2, float y2, long tq) {
	auto p_bucket = get_mutable_instance()[col][row].get(); {
		lock_guard<mutex>{g_mutex[col][row]};
		g_reader[col][row] += 1;
		for (int i = p_bucket->current_ - 1; i >= 0; i--) {
			if (p_bucket->sites_[i].x >= x1 && p_bucket->sites_[i].x <= x2
				&& p_bucket->sites_[i].y >= y1 && p_bucket->sites_[i].y <= y2
				&& (p_bucket->sites_[i].tu >= tq || -p_bucket->sites_[i].tu >= tq))
				result.emplace_back(p_bucket->sites_[i]);
		}
	}
	p_bucket = p_bucket->next_.get();
	while (p_bucket) {
		for (int i = p_bucket->current_ - 1; i >= 0; i--)
			if (p_bucket->sites_[i].x >= x1 && p_bucket->sites_[i].x <= x2
				&& p_bucket->sites_[i].y >= y1 && p_bucket->sites_[i].y <= y2
				&& (p_bucket->sites_[i].tu >= tq || -p_bucket->sites_[i].tu >= tq))
				result.emplace_back(p_bucket->sites_[i]);
		p_bucket = p_bucket->next_.get();
	}

	g_reader[col][row] -= 1;
}

void Grid::MoveSite(int id, float x, float y) {

	auto& si = SecondaryIndex::get_mutable_instance();
	auto p = si.find(id);
	if (p == si.end()) {
		AddSite(id, x, y);
		return;
	}
	int row = get_coordinate(y);
	int col = get_coordinate(x);

	lock_guard<mutex>{s_mutex[id]};
	auto ptr = &p->second;
	if (ptr->col == col && ptr->row == row) {// local update
		auto p_site = ptr->p_bucket->sites_.begin() + ptr->index;
		p_site->x = x;
		p_site->y = y;
		p_site->tu = static_cast<long int>(time(nullptr));
	}
	else {// non-local update
		if (ptr->row_ld >= 0)
		// ReSharper disable once CppPossiblyErroneousEmptyStatements
			while (RemoveFromCell(id, ptr->col_ld, ptr->row_ld) == false);
		auto added = AddToCell(id, x, y, col, row);
		ptr->p_bucket->sites_[ptr->index].tu = -ptr->p_bucket->sites_[ptr->index].tu;
		ptr->RollInValues(added.first, added.second, col, row);
	}
}

void Grid::Query(vector<Site>& result, float x1, float y1, float x2, float y2, long int tq) {
	int cx1 = get_coordinate(x1);
	int cy1 = get_coordinate(y1);
	int cx2 = get_coordinate(x2);
	int cy2 = get_coordinate(y2);

	for (int ax = cx1 + 1; ax < cx2; ax++)
		for (int ay = cy1 + 1; ay < cy2; ay++)
			RetrieveAllSitesInCell(result, ax, ay);

	for (int x = cx1 + 1; x < cx2; x++) {
		RetrieveSitesInCell(result, x, cy1, x1, y1, x2, y2, tq);
		RetrieveSitesInCell(result, x, cy2, x1, y1, x2, y2, tq);
	}
	for (int y = cy1; y <= cy2; y++) {
		RetrieveSitesInCell(result, cx1, y, x1, y1, x2, y2, tq);
		RetrieveSitesInCell(result, cx2, y, x1, y1, x2, y2, tq);
	}

	vector<Site> unique_result_sites;
	bool found_one = false;
	for (auto& r : result) {
		for (auto& u : unique_result_sites) {
			if (u.id == r.id) {
				if (u.tu < 0) u = r;
				found_one = true;
				break;
			}
		}
		if (!found_one)
			unique_result_sites.push_back(r);
	}

	result.swap(unique_result_sites);
}

