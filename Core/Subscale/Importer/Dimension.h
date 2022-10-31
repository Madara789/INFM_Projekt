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
    [[nodiscard]] const Points &getPoints() const;
    [[nodiscard]] uint32_t getId() const;

    friend std::ostream &operator<<(std::ostream &os, const Dimension &dimension);
};

typedef std::vector<Dimension> Dimensions;