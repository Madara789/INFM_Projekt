#pragma once

#include "../DenseUnitGeneratorInterface.h"

class SequentialDenseUnitGenerator : public DenseUnitGeneratorInterface
{
private:
	DenseUnits generateCombinations(const CoreSet& coreSet, uint32_t sizeOfCombinations, uint64_t minSigBoundary, uint64_t maxSigBoundary, const uint64_t* labeledData);
	void generateAllCombinationsOfCoreSet(const Points& points, Points denseUnits[], uint32_t start, uint32_t end, uint32_t currentIndex, uint32_t sizeOfCombinations);
	static uint64_t calculateSignatureFromPoints(const Points& points, const uint64_t* labeledData);

public:
	DenseUnits *getDenseUnits(const std::vector<CoreSets>& coreSets, uint32_t minPoints, uint64_t minSigBoundary, uint64_t maxSigBoundary, const uint64_t* labeledData) override;
};