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
	auto qt = make_shared<QuadTree>();
	ASSERT_EQ(qt->IsLeaf(), true);
	qt->children[0] = make_unique<QuadTree>();
	ASSERT_EQ(qt->IsLeaf(), false);
}

