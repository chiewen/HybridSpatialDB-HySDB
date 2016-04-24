#pragma once

#include <gtest/gtest.h>
#include <site.h>
#include <grid.h>
#include <iostream> 
#include <secondary_index.h>
#include <xmmintrin.h>
#include <parallel_quad_tree.h>
#include <atomic>
#include <index.h>

using namespace std;

struct tt {
	int a;
	tt* next;
};

TEST(ParallelMOD, QuadTree) {
	auto& qt = QuadTree::root_tree_;
	ASSERT_EQ(qt.IsLeaf(), true);
	qt.Split();
	ASSERT_EQ(qt.IsLeaf(), false);
	qt.AddSite(0, 1, 1);
	ASSERT_EQ(qt.children[2].get()->ptr_bucket_->current_, 1);
	ASSERT_EQ(qt.children[0].get()->ptr_bucket_->current_, 0);
	qt.children[2]->Split();
	qt.AddSite(1, 1, 2);

	//auto swapped = p_quad_tree->ptr_bucket_->Del(0);
	//ASSERT_EQ(get<4>(swapped), true);
	qt.RemoveSite(0);
	ASSERT_EQ(qt.children[2].get()->ptr_bucket_->current_, 0);

	qt.MoveSite(1, 2, 3);
	ASSERT_EQ(qt.children[2].get()->ptr_bucket_->current_, 0);
	ASSERT_EQ(qt.children[2]->children[2].get()->ptr_bucket_->current_, 1);

	qt.children[2]->Merge();
	ASSERT_EQ(qt.children[2].get()->ptr_bucket_->current_, 1);

//	cout << sizeof(array<unique_ptr<QuadTree>, 4>) << endl;
	
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

