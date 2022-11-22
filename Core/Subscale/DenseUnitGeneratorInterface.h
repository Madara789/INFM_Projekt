#pragma once

#include "DenseUnitGenerator/DenseUnit.h"
#include "CoreSetSeeker/CoreSet.h"

class DenseUnitGeneratorInterface {
public:
	virtual DenseUnits &getDenseUnits(const CoreSets& coreSets, uint32_t minPoints, uint64_t min, uint64_t max) = 0;
};