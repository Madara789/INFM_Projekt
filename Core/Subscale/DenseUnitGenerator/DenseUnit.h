#pragma once

#include "../Importer/Point.h"

#include <vector>
#include <cstdint>

class DenseUnit {
private:
	Points points_;
	uint64_t signature_;
	uint64_t dimension_;

public:
	DenseUnit(Points points, uint64_t signature, uint64_t dimension);
	Points getPoints();
	uint64_t getSignature() const;
    uint64_t getDimension() const;
};

typedef std::vector<DenseUnit> DenseUnits;