#include "stdafx.h"
#include "simple_simulator.h"
#include <iostream>

simple_simulator::simple_simulator(
	float length, float width, float speed, int object_num): length(length),
	                                                         width(width), object_num(object_num),
	                                                         objects(std::vector<obj>(object_num)) {
	int i = 0;
	for (auto& o : objects) {
		o.id = i++;
		o.speed = speed;
		o.x = rand() % static_cast<int>(width);
		o.y = rand() % static_cast<int>(length);
		o.direction = (rand() % 628) / 100.0;
	}
}

update_info simple_simulator::update() {
	auto& o = objects[current++];
	if (current == object_num) current = 0;

	o.x += o.speed * cos(o.direction);
	o.y += o.speed * sin(o.direction);

	if (o.x > width || o.x < 0) o.direction = 3.14 - o.direction;
	if (o.y > length || o.y < 0) o.direction *= -1;

	if (o.direction < 0) o.direction += 6.28;

	//std::cout << "=========" << o.direction << " " << o.x << " " << o.y << std::endl;
	return update_info(o);
}
