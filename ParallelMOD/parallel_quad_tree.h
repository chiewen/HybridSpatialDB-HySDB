#include <array>
#include <memory>
#include "gtest/gtest_prod.h"

using namespace std;

class QuadTree
{
	FRIEND_TEST(ParallelMOD, QuadTree);
	array<unique_ptr<QuadTree>, 4> children;

public:
	inline bool IsLeaf();
	void Balance();
	void AddSite(int id, int x, int y);
	void MoveSite(int id, int x, int y);
};

bool QuadTree::IsLeaf() {
	return all_of(children.begin(), children.end(), [](unique_ptr<QuadTree>& p) {
		return p.get() == nullptr;
	});
}