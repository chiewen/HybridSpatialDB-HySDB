#pragma once
#include "bucket.h"

class SecondaryElement {
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

	SecondaryElement(Bucket* b, unsigned i, int row, int col);
	void RollInValues(Bucket* b, unsigned i, int row, int col);
};

