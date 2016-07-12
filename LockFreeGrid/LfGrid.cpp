#include "LfGrid.h"
#include <secondary_index.h>

void LfGrid::Clear() {
	for (int i = 0; i < kGridWidth; i++)
		for (int j = 0; j < kGridWidth; j++)
			grid[i][j] = move(make_unique<LfBucket>());
}

void LfGrid::MoveSite(int id, int x, int y) {
//	auto& si = SecondaryIndex::get_mutable_instance();
//	auto p = si.find(id);
//	if (p == si.end()) {
//		AddSite(id, x, y);
//		return;
//	}
	int row = get_coordinate(y);
	int col = get_coordinate(x);

//	lock_guard<mutex>{s_mutex[id]};
//	auto ptr = &p->second;
//	if (ptr->col == col && ptr->row == row) {// local update
//		auto p_site = ptr->p_bucket->sites_.begin() + ptr->index;
//		p_site->SetValue(x, y, static_cast<int>(time(nullptr)));
//	}
//	else {// non-local update
//		if (ptr->row_ld >= 0)
//			 ReSharper disable once CppPossiblyErroneousEmptyStatements
//			while (RemoveFromCell(id, ptr->col_ld, ptr->row_ld) == false);
		auto added = MoveToCell(id, x, y, col, row);
//		ptr->p_bucket->sites_[ptr->index].NegateTime();
//		ptr->RollInValues(added.first, added.second, col, row);
//	}
}

void LfGrid::Query(vector<SiteValue>& result, int x1, int y1, int x2, int y2, int tq) {
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

	vector<SiteValue> unique_result_sites;
	for (auto& r : result) {
		bool found_one = false;
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

pair<LfBucket*, unsigned> LfGrid::MoveToCell(int id, int x, int y, int col, int row) {
	if (grid[col][row]->is_full()) {
		auto new_bucket = make_unique<LfBucket>();
		new_bucket->next_ = move(grid[col][row]);
		grid[col][row] = move(new_bucket);
	}

	return grid[col][row]->Add(id, x, y);
}

void LfGrid::RetrieveAllSitesInCell(vector<SiteValue>& result, int col, int row) {
	auto p_bucket = get_mutable_instance().grid[col][row].get(); {
//		for (int i = p_bucket->current_ - 1; i >= 0; i--)
//			result.emplace_back(p_bucket->sites_[i].Value());
	}
//	p_bucket = p_bucket->next_.get();
	while (p_bucket) {
//		for (int i = p_bucket->current_ - 1; i >= 0; i--)
//			result.emplace_back(p_bucket->sites_[i].Value());
//		p_bucket = p_bucket->next_.get();
	}
}

void LfGrid::RetrieveSitesInCell(vector<SiteValue>& result, int col, int row, int x1, int y1, int x2, int y2, int tq) {
	auto p_bucket = get_mutable_instance().grid[col][row].get(); {
//		for (int i = p_bucket->current_ - 1; i >= 0; i--) {
//			auto site = p_bucket->sites_[i].Value();
//			if (site.x >= x1 && site.x <= x2
//				&& site.y >= y1 && site.y <= y2
//				&& (site.tu >= tq || site.tu >= tq))
//				result.emplace_back(p_bucket->sites_[i].Value());
//		}
	}
//	p_bucket = p_bucket->next_.get();
	while (p_bucket) {
//		for (int i = p_bucket->current_ - 1; i >= 0; i--) {
//			auto site = p_bucket->sites_[i].Value();
//			if (site.x >= x1 && site.x <= x2
//				&& site.y >= y1 && site.y <= y2
//				&& (site.tu >= tq || -site.tu >= tq))
//				result.emplace_back(p_bucket->sites_[i].Value());
//		}
//		p_bucket = p_bucket->next_.get();
	}
}
