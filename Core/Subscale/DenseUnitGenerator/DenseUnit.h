#pragma once

#include "../Importer/Point.h"

#include <vector>

class DenseUnit {
private:
	Points points_;
	uint64_t signature_;
	uint32_t dimension_;

public:
	Points getPoints();
	uint64_t getSignature() const;
	uint32_t getDimension() const;
};

typedef std::vector<DenseUnit> DenseUnits;