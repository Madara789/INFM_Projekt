#pragma once

#include "Point.h"

#include <vector>

class CoreSet {
private:
	Points points_;

public:
	CoreSet();
	CoreSet(Points);
	void addPoint(Point* point);
	uint32_t getSize();
};

typedef std::vector<CoreSet> CoreSets;