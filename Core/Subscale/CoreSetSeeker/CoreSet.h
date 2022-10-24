#pragma once

#include "../Importer/Point.h"

#include <vector>

class CoreSet {
private:
	Points points_;
    uint32_t dimension_;

public:
	CoreSet();
	explicit CoreSet(uint32_t);
	void addPoint(Point* point);
    size_t getSize();
    const Points &getPoints() const;
    uint32_t getDimension() const;
};

typedef std::vector<CoreSet> CoreSets;