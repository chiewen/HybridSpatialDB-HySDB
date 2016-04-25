#pragma once
#include "site.h"
#include <vector>

class SiteContainer {
public:
	virtual ~SiteContainer() = default;

	static void AddSite(int id, int x, int y);
	static void DelSite(int id);
	static void MoveSite(int id, int x, int y);

	virtual void Query(vector<SiteValue>& result, int x1, int y1, int x2, int y2, int tq) = 0;
};
