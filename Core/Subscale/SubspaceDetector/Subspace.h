#pragma once

#include "../DenseUnitGenerator/DenseUnit.h"

#include <vector>
#include <map>

class Subspace {
private:
	DenseUnits denseUnits_;
	std::vector<uint32_t> dimensions_;

public:
    explicit Subspace(const DenseUnit &denseUnit);

    DenseUnits getDenseUnits();
	std::vector<uint32_t> getDimensions();
    void addDenseUnit(const DenseUnit &denseUnit);
};

typedef std::map<uint64_t, Subspace*> Subspaces;