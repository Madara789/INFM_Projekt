#pragma once

#include "DenseUnitGenerator/DenseUnit.h"
#include "CoreSetSeeker/CoreSet.h"

class DenseUnitGeneratorInterface {
public:
	virtual DenseUnits getDenseUnits(CoreSets coreSets, uint32_t minPoints) = 0;
};