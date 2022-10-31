#pragma once

#include "DenseUnitGenerator/DenseUnit.h"
#include "CoreSetSeeker/CoreSet.h"

class DenseUnitGeneratorInterface {
public:
	virtual DenseUnits &getDenseUnits(const CoreSets& coreSets, uint32_t minPoints) = 0;
};