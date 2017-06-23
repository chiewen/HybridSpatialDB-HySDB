#pragma once
#include "moving_simulator.h"
#include <vector>

struct obj {
	long id;
	float x;
	float y;
	float speed;
	float direction;
};

class simple_simulator : public moving_simulator{
private:
	float length;
	float width;

	int current = 0; 
	int object_num;

public:
	std::vector<obj> objects;

	simple_simulator(float length, float width, float speed, int object_num);

	update_info update() override;
};
