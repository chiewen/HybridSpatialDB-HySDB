#pragma once
#include <vector>
#include "update_info.h"

using namespace std;

class SiteArranger {
public:
	const int SITE_NUM = 10000;

	static vector<UpdateInfo> updates_;

	static void ReadData(const string& path);
};

