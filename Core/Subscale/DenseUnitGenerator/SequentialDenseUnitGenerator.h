#pragma once

#include "../DenseUnitGeneratorInterface.h"

class SequentialDenseUnitGenerator : public DenseUnitGeneratorInterface
{
private:
	DenseUnits generateCombinations(CoreSet coreSet, int sizeOfCombinations);
	void generateAllCombinationsOfCoreSet(Points points, Points denseUnits[], int start, int end, int currentIndex, int sizeOfCombinations);
	uint64_t calculateSignatureFromPoints(Points points);

public:
	DenseUnits getDenseUnits(CoreSets coreSets, int minPoints) override;
};