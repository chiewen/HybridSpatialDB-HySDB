#include "secondary_element.h"

SecondaryElement::SecondaryElement(Bucket* p_bucket, unsigned index, int col, int row)
	: p_bucket(p_bucket), index(index), row(row), col(col),
	p_bucket_ld(nullptr), index_ld(0), row_ld(-1), col_ld(-1) {}

void SecondaryElement::RollInValues(Bucket* p_bucket, unsigned index, int col, int row) {
	p_bucket_ld = this->p_bucket;
	index_ld = this->index;
	row_ld = this->row;
	col_ld = this->col;

	this->p_bucket = p_bucket;
	this->index = index;
	this->row = row;
	this->col = col;
}

