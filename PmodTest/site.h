#pragma once

#include <gtest/gtest.h>
#include <Site.h>

TEST(Trajectory, Simple) {
	Site s;
	s.discribe();
	ASSERT_EQ(220, 220);
}

TEST(Trajectory, Simple2) {

	ASSERT_EQ(220, 220);
}
