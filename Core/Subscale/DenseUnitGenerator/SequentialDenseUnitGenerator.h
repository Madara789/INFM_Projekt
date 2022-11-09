#pragma once

#include "../DenseUnitGeneratorInterface.h"

class SequentialDenseUnitGenerator : public DenseUnitGeneratorInterface
{
private:
	DenseUnits generateDenseUnits(const CoreSet &coreSet, const uint32_t minPoints);
	void calculateCombinations(const Points &points, Points combinations[], const uint32_t minPoints);
	Points *generateTmpPoints(const uint32_t minPoints);
	void fillCombinationToLeft(Points tmpCombination[], const Points &points, uint32_t &depth, uint32_t &pointIndex);
	void addNewCombination(Points combinations[], const Points tmpCombination[]);
	bool replaceCombinationWithNewPoint(Points ka[], uint32_t &depth, const Points &points, uint32_t &pointIndex);
	void calculateNewPointIndex(uint32_t &pointIndex, uint32_t &depth, const Points tmpCombination[], const Points &points);
	uint64_t calculateSignature(const Points &points);

public:
	DenseUnits &getDenseUnits(const CoreSets &coreSets, const uint32_t minPoints) override;
};