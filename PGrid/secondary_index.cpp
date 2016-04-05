#include "secondary_index.h"

void SecondaryIndex::RenewSwappedSite(int id, Bucket* p_bucket, unsigned index, bool is_real) {
	auto p = find(id);
	assert(p != end());

	auto &element = p->second;
	if (is_real) {
		element.p_bucket = p_bucket;
		element.index = index;
	}
	else {
		element.p_bucket_ld = p_bucket;
		element.index_ld = index;
	}
}