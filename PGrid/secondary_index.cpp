#include "secondary_index.h"

SecondaryElement* SecondaryIndex::GetById(int id) {
	auto & si = get_mutable_instance();
	auto p = si.find(id);
	if (p == si.end()) return nullptr;
	return &p->second;
}


void SecondaryIndex::RenewPlaceChangedSite(int id, Bucket* p_bucket, unsigned index, bool is_real) {
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