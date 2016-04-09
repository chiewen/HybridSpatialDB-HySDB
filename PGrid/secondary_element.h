#pragma once
#include "bucket.h"

class SecondaryElement {
	FRIEND_TEST(Container, Grid);
	friend class Grid;
	friend class SecondaryIndex;

	Bucket* p_bucket;
	unsigned index;
	int row;
	int col;

	Bucket* p_bucket_ld;
	unsigned index_ld;
	int row_ld;
	int col_ld;

	SecondaryElement(Bucket* b, unsigned i, int col, int row);
	void RollInValues(Bucket* b, unsigned i, int col, int row);
};

