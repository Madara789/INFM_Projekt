#pragma once

#include "DenseUnitGenerator/DenseUnit.h"
#include "CoreSetSeeker/CoreSet.h"

class DenseUnitGeneratorInterface {
public:
	virtual DenseUnits *getDenseUnits(const std::vector<CoreSets>& coreSets, uint32_t minPoints, uint64_t minSigBoundary, uint64_t maxSigBoundary) = 0;
    virtual ~DenseUnitGeneratorInterface() = default;
};