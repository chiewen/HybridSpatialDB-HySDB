#pragma once

#include <unordered_map>
#include "secondary_element.h"
#include <boost/serialization/singleton.hpp>

using namespace std;
using boost::serialization::singleton;

class SecondaryIndex : public unordered_map<int, SecondaryElement>, public singleton<SecondaryIndex> { 
public:
	static SecondaryElement* GetById(int id);
};

