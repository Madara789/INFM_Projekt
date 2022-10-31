#pragma once

#include "../DenseUnitGeneratorInterface.h"

class SequentialDenseUnitGenerator : public DenseUnitGeneratorInterface
{
private:
	DenseUnits generateCombinations(const CoreSet& coreSet, uint32_t sizeOfCombinations);
	void generateAllCombinationsOfCoreSet(const Points& points, Points denseUnits[], uint32_t start, uint32_t end, uint32_t currentIndex, uint32_t sizeOfCombinations);
	static uint64_t calculateSignatureFromPoints(const Points& points);

public:
	DenseUnits &getDenseUnits(const CoreSets& coreSets, uint32_t minPoints) override;
};