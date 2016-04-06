#pragma once

#include <unordered_map>
#include "secondary_element.h"
#include <boost/serialization/singleton.hpp>

using namespace std;
using boost::serialization::singleton;

class SecondaryIndex : public unordered_map<int, SecondaryElement>,
                       public singleton<SecondaryIndex> {
	friend Grid;
	void RenewSwappedSite(int id, Bucket* p_bucket, unsigned pos, bool is_real);
};

