#pragma once

#pragma once

#include <unordered_map>
#include "element.h"
#include <boost/serialization/singleton.hpp>

class Bucket;
class QuadTree;
using namespace std;
using boost::serialization::singleton;

class Index : public unordered_map<int, Element>,
	public singleton<Index> {
	FRIEND_TEST(ParallelMOD, QuadTree);
	friend QuadTree;
	void RenewSwappedSite(int id, Bucket* bucket, unsigned index);
};

