#include "SequentialDenseUnitGenerator.h"

DenseUnits SequentialDenseUnitGenerator::getDenseUnits(CoreSets coreSets, int minPoints)
{
    DenseUnits denseUnits;

    for (auto coreSet : coreSets)
    {
        DenseUnits denseUnitsOfCoreSet = generateCombinations(coreSet, minPoints);
        denseUnits.insert(denseUnits.end(), denseUnitsOfCoreSet.begin(), denseUnitsOfCoreSet.end());
    }

    return denseUnits;
}

void SequentialDenseUnitGenerator::generateAllCombinationsOfCoreSet(Points points, Points combinations[], int start, int end, int currentIndex, int sizeOfCombinations)
{
    if (currentIndex == sizeOfCombinations)
        return;

    // The condition "end - i + 1 >= sizeOfCombinations - currentIndex" makes sure that including one element at index will make a combination with remaining elements at remaining positions
    for (int i = start; i < end && end - i + 1 >= sizeOfCombinations - currentIndex; i++)
    {
        combinations[currentIndex].push_back(points[i]);
        generateAllCombinationsOfCoreSet(points, combinations, start, end, currentIndex + 1, sizeOfCombinations);
    }
}

DenseUnits SequentialDenseUnitGenerator::generateCombinations(CoreSet coreSet, int minPoints)
{
    Points combinations[minPoints];
    generateAllCombinationsOfCoreSet(coreSet.getPoints(), combinations, 0, coreSet.getSize() - 1, 0, minPoints);

    DenseUnits denseUnitsOfCoreSet;
    for (auto combination : combinations)
    {
        uint64_t signature = calculateSignatureFromPoints(combination);

        denseUnitsOfCoreSet.push_back(DenseUnit(combination, signature, coreSet.getDimension()));
    }

    return denseUnitsOfCoreSet;
}

uint64_t SequentialDenseUnitGenerator::calculateSignatureFromPoints(Points points)
{
    uint64_t signature;
    for (auto point : points)
    {
        signature += point->getSignature();
    }
    return signature;
}
