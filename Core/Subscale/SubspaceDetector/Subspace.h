#pragma once

#include "../DenseUnitGenerator/DenseUnit.h"

#include <vector>
#include <map>
#include <ostream>

class Subspace {
private:
	DenseUnits denseUnits_;
	std::vector<uint32_t> dimensions_;

public:
    explicit Subspace(const DenseUnit &denseUnit);

    DenseUnits getDenseUnits();
	std::vector<uint32_t> getDimensions();
    void addDenseUnit(const DenseUnit &denseUnit);
    friend std::ostream &operator<<(std::ostream &os, const Subspace &subspace);
};

typedef std::map<uint64_t, Subspace*> Subspaces;