#pragma once

#include "DenseUnitGenerator/DenseUnit.h"
#include "CoreSetSeeker/CoreSet.h"

class DenseUnitGeneratorInterface {
public:
	virtual DenseUnits getDenseUnits(CoreSets) = 0;
};