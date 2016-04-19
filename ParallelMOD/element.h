#pragma once
#include "bucket.h"

class Element {
public:
	FRIEND_TEST(ParallelMOD, QuadTree);
	friend class Index;

	Bucket* p_bucket;
	unsigned index;


	Element(Bucket* b, unsigned i) : p_bucket(b), index(i) {};
};
