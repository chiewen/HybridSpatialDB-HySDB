#pragma once

#include <gtest/gtest.h>
#include <iostream>
#include "simple_simulator.h"

using namespace std;

TEST(DataProvider, Construct) {
	simple_simulator ss(100, 100, 10, 2);
	for (int i = 0; i < 100; i++) {
		auto o = ss.update();
		cout << i << ": " << o.id << " " << o.x << ", " << o.y << endl;
	}
	ASSERT_EQ(1, 1);
}