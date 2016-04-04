#include "secondary_index.h"

SecondaryElement* SecondaryIndex::GetById(int id) {
	auto & si = get_mutable_instance();
	auto p = si.find(id);
	if (p == si.end()) return nullptr;
	return &p->second;
}

