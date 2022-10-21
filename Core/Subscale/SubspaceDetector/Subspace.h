#pragma once

#include "../DenseUnitGenerator/DenseUnit.h"

#include <vector>

class Subspace {
private:
	DenseUnits denseUnits_;
	std::vector<uint32_t> dimensions_;

public:
	DenseUnits getDenseUnits();
	std::vector<uint32_t> getDimensions();
};

typedef std::vector<Subspace> Subspaces;