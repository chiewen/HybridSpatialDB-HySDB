#pragma once

#include "LfBucket.h"

struct IdElement {
	IdElement(LfBucket* const p_bucket, const unsigned index, const int col, const int row)
		: p_bucket_{p_bucket},
		  index{index},
		  row{row},
		  col{col} {}

	LfBucket* p_bucket_;
	unsigned index;
	int col;
	int row;
};