#pragma once

#include "../DenseUnitGeneratorInterface.h"

class SequentialDenseUnitGenerator : public DenseUnitGeneratorInterface
{
private:
    uint64_t choose(uint64_t n, uint64_t k);
    uint64_t largestV(uint64_t a, uint64_t b, uint64_t x);
    void elements(uint64_t m, uint64_t n, uint64_t k, uint64_t* ans);
public:
	DenseUnits *getDenseUnits(const std::vector<CoreSets>& coreSets, uint32_t minPoints, uint64_t minSigBoundary, uint64_t maxSigBoundary) override;
};