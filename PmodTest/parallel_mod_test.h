#pragma once

#include <gtest/gtest.h>
#include <site.h>
#include <grid.h>
#include <iostream> 
#include <secondary_index.h>
#include <xmmintrin.h>
#include <parallel_quad_tree.h>

using namespace std;

TEST(ParallelMOD, QuadTree) {
	auto qt = make_shared<QuadTree>(make_unique<Bucket>(), 0, 100, 0, 100);
	ASSERT_EQ(qt->IsLeaf(), true);
	qt->Split();
	ASSERT_EQ(qt->IsLeaf(), false);

	cout << sizeof(array<unique_ptr<QuadTree>, 4>) << endl;
}

