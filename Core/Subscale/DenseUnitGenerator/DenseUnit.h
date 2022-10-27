#pragma once

#include "../Importer/Point.h"

#include <vector>
#include <cstdint>
#include <ostream>

class DenseUnit {
private:
	Points points_;
	uint64_t signature_;
    uint32_t dimension_;

public:
	DenseUnit(Points points, uint64_t signature, uint32_t dimension);
	Points getPoints();
	uint64_t getSignature() const;
    uint32_t getDimension() const;
    friend std::ostream &operator<<(std::ostream &os, const DenseUnit &unit);
};

typedef std::vector<DenseUnit> DenseUnits;