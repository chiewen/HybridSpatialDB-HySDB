#include "secondary_element.h"

SecondaryElement::SecondaryElement(Bucket* b, unsigned i, int row, int col)
	: p_bucket(b), index(i), row(row), col(col),
	p_bucket_ld(nullptr), index_ld(0), row_ld(0), col_ld(0) {}

void SecondaryElement::RollInValues(Bucket* b, unsigned i, int row, int col) {
	p_bucket_ld = p_bucket;
	index_ld = index;
	row_ld = row;
	col_ld = col;

	p_bucket = b;
	index = i;
	this->row = row;
	this->col = col;
}

