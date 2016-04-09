#pragma once

#include <gtest/gtest.h>
#include <site.h>
#include <grid.h>
#include <iostream> 
#include <secondary_index.h>

using namespace std;

TEST(Container, Site) {
	Site s(3, 2, 1);
	cout << s.x << endl;
	ASSERT_EQ(s.id, 3);
	ASSERT_EQ(s.x, 2);
	ASSERT_EQ(s.y, 1);
}

TEST(Container, Bucket) {
	ASSERT_EQ((1 << 16) * sizeof(unique_ptr<Bucket>), sizeof(Grid::get_const_instance()) - 4);
	ASSERT_EQ(Grid::get_const_instance()[0][0]->next_, nullptr);
}

TEST(Container, Grid) {
	float x = 4 * (1 << kSpacePerCellBitwise) + 1;
	float y = 3 * (1 << kSpacePerCellBitwise) + 1;
	float x1 = 6 * (1 << kSpacePerCellBitwise) + 1;
	float y1 = 5 * (1 << kSpacePerCellBitwise) + 1;

	auto& grid = Grid::get_mutable_instance();
	grid.Clear();

	ASSERT_EQ(grid[4][3]->current_, 0);

	for (int i = 0; i < 3; i++)
		grid.AddSite(i, x, y);

	ASSERT_EQ(grid[4][3]->current_, 3);

	for (int i = 3; i <= Bucket::kSize; i++)
		grid.AddSite(i, x, y);

	auto & si = SecondaryIndex::get_const_instance();
	auto p = si.find(12);

	ASSERT_EQ(p->second.col, 4);
	ASSERT_EQ(p->second.col_ld, -1);

	ASSERT_EQ(grid[4][3]->next_->current_, Bucket::kSize);
	ASSERT_EQ(grid[4][3]->current_, 1);

	grid.DelSite(100);
	ASSERT_EQ(grid[4][3]->current_, 1);

	grid.DelSite(32);
	ASSERT_EQ(grid[4][3]->current_, Bucket::kSize);

	grid.DelSite(11);
	ASSERT_EQ(grid[4][3]->current_, Bucket::kSize - 1);

	grid.MoveSite(12, x + 2, y + 2);
	ASSERT_EQ(grid[4][3]->current_, Bucket::kSize - 1);
	ASSERT_EQ(grid[0][0]->current_, 0);
	grid.MoveSite(12, 1, 1);
	ASSERT_EQ(grid[4][3]->current_, Bucket::kSize - 1);
	ASSERT_EQ(grid[0][0]->current_, 1);
	ASSERT_EQ(p->second.col, 0);
	ASSERT_EQ(p->second.col_ld, 4);
	grid.MoveSite(12, x1, y1);
	ASSERT_EQ(grid[4][3]->current_, Bucket::kSize - 2);
	ASSERT_EQ(grid[0][0]->current_, 1);
	ASSERT_EQ(grid[6][5]->current_, 1);
	//grid.MoveSite(13, 1, 1);
	grid.MoveSite(13, x1, y1);
	grid.MoveSite(14, x1, y1);
	ASSERT_EQ(grid[6][5]->current_, 3);

	vector<Site> result;
	grid.Query(result, 0, 0, x1+10, y1+10, static_cast<long int>(time(nullptr) - 100000));

	ASSERT_EQ(result.size(), 31);

}

