#pragma once

#include "../Importer/Point.h"

#include <vector>
#include <ostream>

class CoreSet {
private:
	Points points_;
    uint32_t dimension_;

public:
	explicit CoreSet(uint32_t);
    void addPoint(Point* point);
    [[nodiscard]] const Points &getPoints() const;
    [[nodiscard]] uint32_t getDimension() const;
    friend std::ostream &operator<<(std::ostream &os, const CoreSet &set);
};

typedef std::vector<CoreSet> CoreSets;