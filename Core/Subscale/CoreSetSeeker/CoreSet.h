#pragma once

#include "../Importer/Point.h"

#include <vector>

class CoreSet {
private:
	Points points_;

public:
	CoreSet();
	CoreSet(Points);
	void addPoint(Point* point);
    int32_t getSize();
};

typedef std::vector<CoreSet> CoreSets;