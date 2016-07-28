#pragma once

#include <unordered_map>
#include <boost/serialization/singleton.hpp>
#include "IdElement.h"

using namespace std;
using boost::serialization::singleton;


class IdIndex : public unordered_map<int, IdElement>,
	public singleton<IdIndex> {
};

