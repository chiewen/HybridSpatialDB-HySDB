#pragma once
#include "bucket.h"

struct SecondaryElement {
	Bucket* p_bucket;
	unsigned index;
	int row;
	int col;

	Bucket* p_bucket_ld;
	unsigned index_ld;
	int row_ld;
	int col_ld;

	SecondaryElement(Bucket* b, unsigned i, int row, int col);
	void RefreshValues(Bucket* b, unsigned i, int row, int col);
};

