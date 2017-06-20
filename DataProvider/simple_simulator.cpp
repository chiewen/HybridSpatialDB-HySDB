#include "stdafx.h"
#include "simple_simulator.h"

simple_simulator::simple_simulator(
	float length, float width, int object_num): length(length),
                                                                               width(width),
                                                                               objects(std::vector<obj>(object_num)) {
	int i = 0;
	for (auto& o : objects) {
		o.id = i++;
		o.x = rand() % static_cast<int>(width);
		o.y = rand() % static_cast<int>(length);
		o.direction = rand() % 10;
	}
}

update_info simple_simulator::update() {
	
}
