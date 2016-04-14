#include "parallel_quad_tree.h"


QuadTree::QuadTree(unique_ptr<Bucket> && bucket) : ptr_bucket_(move(bucket)) {}

void QuadTree::Balance() {}

void QuadTree::AddSite(int id, int x, int y) {}

void QuadTree::MoveSite(int id, int x, int y) {}

void QuadTree::Split() {

}
