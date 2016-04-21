#include "index.h"

void Index::RenewSwappedSite(int id, Bucket* p_bucket, unsigned index) {
	auto p = find(id);
	assert(p != end());

	auto& element = p->second;
	element.p_bucket = p_bucket;
	element.index = index;
}
