#pragma once

#include "../DenseUnitGeneratorInterface.h"

class SequentialDenseUnitGenerator : public DenseUnitGeneratorInterface
{
	DenseUnits getDenseUnits(CoreSets);
};