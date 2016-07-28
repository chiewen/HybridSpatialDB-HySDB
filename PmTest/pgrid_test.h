#pragma once

#include <gtest/gtest.h>
#include <site.h>
#include <grid.h>
#include <iostream> 
#include <secondary_index.h>
#include <xmmintrin.h>

using namespace std;

TEST(Container, Site) {
	Site si(3, 2, 1);
	auto s = si.Value();
	cout << s.x << endl;
	ASSERT_EQ(s.id, 3);
	ASSERT_EQ(s.x, 2);
	ASSERT_EQ(s.y, 1);

	auto sv = si.id();
	ASSERT_EQ(3, sv);
}

TEST(Container, Grid) {
	int x = 4 * (1 << kSpacePerCellBitwise) + 1;
	int y = 3 * (1 << kSpacePerCellBitwise) + 1;
	int x1 = 6 * (1 << kSpacePerCellBitwise) + 1;
	int y1 = 5 * (1 << kSpacePerCellBitwise) + 1;

	
	ASSERT_EQ((1 << 16) * sizeof(Bucket*), sizeof(Grid::grid));
	
	auto& grid = Grid::get_mutable_instance();
	grid.Clear();

	ASSERT_EQ(grid.grid[4][3]->current_, 0);

	for (int i = 0; i < 3; i++)
		grid.AddSite(i, x, y);

	ASSERT_EQ(grid.grid[4][3]->current_, 3);

	for (int i = 3; i <= Bucket::kSize; i++)
		grid.AddSite(i, x, y);

	auto & si = SecondaryIndex::get_const_instance();
	auto p = si.find(12);

	ASSERT_EQ(p->second.col, 4);
	ASSERT_EQ(p->second.col_ld, -1);

	ASSERT_EQ(grid.grid[4][3]->next_->current_, Bucket::kSize);
	ASSERT_EQ(grid.grid[4][3]->current_, 1);

	grid.DelSite(100);
	ASSERT_EQ(grid.grid[4][3]->current_, 1);

	grid.DelSite(32);
	ASSERT_EQ(grid.grid[4][3]->current_, Bucket::kSize);

	grid.DelSite(11);
	ASSERT_EQ(grid.grid[4][3]->current_, Bucket::kSize - 1);

	grid.MoveSite(12, x + 2, y + 2);
	ASSERT_EQ(grid.grid[4][3]->current_, Bucket::kSize - 1);
	ASSERT_EQ(grid.grid[0][0]->current_, 0);
	grid.MoveSite(12, 1, 1);
	ASSERT_EQ(grid.grid[4][3]->current_, Bucket::kSize - 1);
	ASSERT_EQ(grid.grid[0][0]->current_, 1);
	ASSERT_EQ(p->second.col, 0);
	ASSERT_EQ(p->second.col_ld, 4);
	grid.MoveSite(12, x1, y1);
	ASSERT_EQ(grid.grid[4][3]->current_, Bucket::kSize - 2);
	ASSERT_EQ(grid.grid[0][0]->current_, 1);
	ASSERT_EQ(grid.grid[6][5]->current_, 1);
	grid.MoveSite(13, 1, 1);
	grid.MoveSite(13, x1, y1);
	grid.MoveSite(14, x1, y1);
	ASSERT_EQ(grid.grid[6][5]->current_, 3);

	vector<SiteValue> result;
	grid.Query(result, 0, 0, x1 + 10, y1 + 10, static_cast<int>(time(nullptr) - 100000));

//	for (auto & s : result)
//		cout << s.id << " ";
//	cout << endl;
	ASSERT_EQ(result.size(), 31);

//	cout << "size of Site" << sizeof Site << endl;
//	cout << "size of Site" << sizeof (int) << endl;
//	cout << "size of Site" << sizeof (long int) << endl;
//	cout << "size of Site" << sizeof (float )<< endl;
//
//	__m128i xm;
//	xm = _mm_set_epi32(1, 2, 3, 4);
//	__m128i xl = _mm_load_si128(&xm);
//
//	//auto si = static_cast<Site> (xl);
//	int o0 = _mm_extract_epi32(xl, 3);
//	int o1 = _mm_extract_epi32(xl, 0);
//
//	cout << endl << "o0: " << o0 << "o1: " << o1;
}

