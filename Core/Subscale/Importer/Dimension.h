#pragma once

#include "Point.h"

class Dimension {
private:
	Points points_;
	uint32_t id_;

public:
	Dimension(uint32_t id, Points points);
	Point* getPoint(uint32_t index);
    int32_t getSize();
	uint32_t getID();
};

typedef std::vector<Dimension> Dimensions;