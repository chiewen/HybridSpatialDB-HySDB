#pragma once
#include "update_info.h"

class moving_simulator {
public:
	virtual ~moving_simulator() = default;
	virtual update_info update() = 0;
};
