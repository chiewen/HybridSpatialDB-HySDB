#pragma once

#include <gtest/gtest.h>
#include <site.h>
#include <grid.h>
#include <iostream> 
#include <secondary_index.h>
#include <xmmintrin.h>
#include <parallel_quad_tree.h>
#include <atomic>

using namespace std;

struct tt {
	int a;
	tt* next;
};

TEST(ParallelMOD, QuadTree) {
	auto qt = make_shared<QuadTree>(make_unique<Bucket>(), 0, 100, 0, 100);
	ASSERT_EQ(qt->IsLeaf(), true);
	qt->Split();
	ASSERT_EQ(qt->IsLeaf(), false);

	cout << sizeof(array<unique_ptr<QuadTree>, 4>) << endl;

//	atomic<tt *> apt = new tt;
//	tt* pt = apt.load();
//	tt* po = pt;
//	tt* pnull = nullptr;
//	pt->next = new tt;
//	pt->next->next = new tt;
//
//	cout << pt << endl;
//	cout << pt->next << endl;
//	cout << pt->next->next << endl;
//
//	ASSERT_EQ(apt.load(), pt);
//	apt.compare_exchange_weak(pt, pt->next);
//	ASSERT_EQ(apt.load(), pt->next);
//	
//	delete pt->next->next;
//	delete pt->next;
//	cout << pt << "a" << endl;
//	delete pt;
//
//	cout << pt << "now" << endl;
//	apt.compare_exchange_weak(po, po->next);

}

