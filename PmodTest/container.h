#pragma once

#include <gtest/gtest.h>
#include <site.h>
#include <grid.h>
#include <iostream> 

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

	auto& grid = Grid::get_mutable_instance();
	grid.RefillEmpty();

	ASSERT_EQ(grid[3][4]->current_, 0);

	for (int i = 0; i < 3; i++)
		grid.AddSite(Site(i, x, y), 3, 4);

	ASSERT_EQ(grid[3][4]->current_, 3);

	for (int i = 3; i <= Bucket::kSize; i++)
		grid.AddSite(Site(i, x, y), 3, 4);

	ASSERT_EQ(grid[3][4]->next_->current_, Bucket::kSize);
	ASSERT_EQ(grid[3][4]->current_, 1);

	grid.DelSite(Site(100, x, y));
	ASSERT_EQ(grid[3][4]->current_, 1);

	grid.DelSite(Site(32, x, y));
	ASSERT_EQ(grid[3][4]->current_, Bucket::kSize);

	grid.DelSite(Site(11, x, y));
	ASSERT_EQ(grid[3][4]->current_, Bucket::kSize - 1);
}

