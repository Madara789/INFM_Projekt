#pragma once

#include "Point.h"
#include <cstdint>
#include <ostream>

class Dimension {
private:
	Points points_;
	uint32_t id_;

public:
	Dimension(uint32_t id, Points points);
	Point* getPoint(uint32_t index);
    size_t getSize();
	uint32_t getID();
    friend std::ostream &operator<<(std::ostream &os, const Dimension &dimension);
};

typedef std::vector<Dimension> Dimensions;