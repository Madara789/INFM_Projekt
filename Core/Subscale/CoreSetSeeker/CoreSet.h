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
    size_t getSize();
};

typedef std::vector<CoreSet> CoreSets;