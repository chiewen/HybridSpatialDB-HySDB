#pragma once
#include "moving_simulator.h"
#include <vector>

class simple_simulator : public moving_simulator{
private:
	float length;
	float width;

	struct obj {
		long id;
		float x;
		float y;
		float direction;
	};

	std::vector<obj> objects;
public:
	simple_simulator(float length, float width, int object_num);

	update_info update() override;
};
