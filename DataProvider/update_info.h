#pragma once

struct obj;

struct update_info {
public:
	long id;
	float x;
	float y;

	update_info(long id, float x, float y)
		: id(id),
		  x(x),
		  y(y) {}
	update_info(const obj&);
};
