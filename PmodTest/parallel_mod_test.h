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
	auto qt = make_shared<QuadTree>(move(make_unique<Bucket>()));
	ASSERT_EQ(qt->IsLeaf(), true);
	qt->children[0] = make_unique<QuadTree>(move(make_unique<Bucket>()));
	//ASSERT_EQ(qt->IsLeaf(), false);

	cout << sizeof(array<unique_ptr<QuadTree>, 4>) << endl;
}

