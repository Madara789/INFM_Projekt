#include <iostream>
#include "SequentialDenseUnitGenerator.h"

DenseUnits *SequentialDenseUnitGenerator::getDenseUnits(const std::vector<CoreSets>& coreSets, uint32_t minPoints, uint64_t minSigBoundary, uint64_t maxSigBoundary, const uint64_t* labeledData)
{
    auto denseUnits = new DenseUnits();

    for (const auto& coreSetOfDimension : coreSets) {
        for (const auto& coreSet : coreSetOfDimension)
        {
            DenseUnits denseUnitsOfCoreSet = generateCombinations(coreSet, minPoints, minSigBoundary, maxSigBoundary, labeledData);
            denseUnits->insert(denseUnits->end(), denseUnitsOfCoreSet.begin(), denseUnitsOfCoreSet.end());
        }
    }

    return denseUnits;
}

void SequentialDenseUnitGenerator::generateAllCombinationsOfCoreSet(const Points& points, Points combinations[], uint32_t start, uint32_t end, uint32_t currentIndex, uint32_t sizeOfCombinations)
{
    if (currentIndex == sizeOfCombinations)
        return;

    // The condition "end - i + 1 >= sizeOfCombinations - currentIndex" makes sure that including one element at index will make a combination with remaining elements at remaining positions
    for (uint32_t i = start; i < end && end - i + 1 >= sizeOfCombinations - currentIndex; i++)
    {
        combinations[currentIndex].push_back(points[i]);
        generateAllCombinationsOfCoreSet(points, combinations, start, end, currentIndex + 1, sizeOfCombinations);
    }
}

DenseUnits SequentialDenseUnitGenerator::generateCombinations(const CoreSet& coreSet, const uint32_t minPoints, uint64_t minSigBoundary, uint64_t maxSigBoundary, const uint64_t* labeledData)
{
    auto* combinations = new Points[minPoints];
    generateAllCombinationsOfCoreSet(coreSet.getPoints(), combinations, 0, (uint32_t) coreSet.getPoints().size() - 1, 0, minPoints);

    DenseUnits denseUnitsOfCoreSet;
    auto* iterator = combinations;
    for (uint32_t i = 0; i < minPoints; i++)
    {
        uint64_t signature = calculateSignatureFromPoints(*iterator, labeledData);

        if (signature >= minSigBoundary && signature < maxSigBoundary)
            denseUnitsOfCoreSet.push_back(DenseUnit(*iterator, signature, coreSet.getDimension()));

        iterator++;
    }
    delete[] combinations;

    return denseUnitsOfCoreSet;
}

 uint64_t SequentialDenseUnitGenerator::calculateSignatureFromPoints(const Points& points, const uint64_t* labeledData)
{
    uint64_t signature = 0;
    for (auto point : points)
    {
        signature += labeledData[point->getSignature()];
    }
    return signature;
}
