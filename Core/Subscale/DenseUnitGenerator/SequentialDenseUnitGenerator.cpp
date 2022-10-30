#include "SequentialDenseUnitGenerator.h"

DenseUnits SequentialDenseUnitGenerator::getDenseUnits(CoreSets coreSets, uint32_t minPoints)
{
    DenseUnits denseUnits;

    for (const auto& coreSet : coreSets)
    {
        DenseUnits denseUnitsOfCoreSet = generateCombinations(coreSet, minPoints);
        denseUnits.insert(denseUnits.end(), denseUnitsOfCoreSet.begin(), denseUnitsOfCoreSet.end());
    }

    return denseUnits;
}

void SequentialDenseUnitGenerator::generateAllCombinationsOfCoreSet(Points points, Points combinations[], uint32_t start, uint32_t end, uint32_t currentIndex, uint32_t sizeOfCombinations)
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

DenseUnits SequentialDenseUnitGenerator::generateCombinations(CoreSet coreSet, const uint32_t minPoints)
{
    auto* combinations = new Points[minPoints];
    generateAllCombinationsOfCoreSet(coreSet.getPoints(), combinations, 0, (uint32_t) coreSet.getSize() - 1, 0, minPoints);

    DenseUnits denseUnitsOfCoreSet;
    auto* iterator = combinations;
    for (uint32_t i = 0; i < minPoints; i++)
    {
        uint64_t signature = calculateSignatureFromPoints(*iterator);

        denseUnitsOfCoreSet.push_back(DenseUnit(*iterator, signature, coreSet.getDimension()));

        iterator++;
    }

    return denseUnitsOfCoreSet;
}

 uint64_t SequentialDenseUnitGenerator::calculateSignatureFromPoints(const Points& points)
{
    uint64_t signature = 0;
    for (auto point : points)
    {
        signature += point->getSignature();
    }
    return signature;
}
