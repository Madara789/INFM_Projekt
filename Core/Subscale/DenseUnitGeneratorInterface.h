#pragma once

#include <vector>

#include "../Data/CoreSet.h"
#include "../Data/DenseUnit.h"

class DenseUnitGeneratorInterface
{
public:
	virtual DenseUnits getDenseUnits(CoreSets) = 0;
};