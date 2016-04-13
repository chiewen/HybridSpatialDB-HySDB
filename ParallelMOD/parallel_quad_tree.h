#include <array>
#include <memory>

using namespace std;

class QuadTree
{
	array<unique_ptr<QuadTree>, 4> children;

public:
	void Balance();
	void AddSite(int id, int x, int y);
	void MoveSite(int id, int x, int y);
};

