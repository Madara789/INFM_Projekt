#include "SequentialDenseUnitGenerator.h"

DenseUnits &SequentialDenseUnitGenerator::getDenseUnits(const CoreSets& coreSets, uint32_t minPoints,  uint64_t min, uint64_t max)
{
    auto denseUnits = DenseUnits();

    for (const auto& coreSet : coreSets)
    {
        DenseUnits denseUnitsOfCoreSet = generateCombinations(coreSet, minPoints);
        for (uint32_t i{}; i < denseUnitsOfCoreSet.size(); i++){
            if (denseUnitsOfCoreSet[i].getSignature() >= min || denseUnitsOfCoreSet[i].getSignature() <= max){
                denseUnits.push_back(denseUnitsOfCoreSet[i]);
            }
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

DenseUnits SequentialDenseUnitGenerator::generateCombinations(const CoreSet& coreSet, const uint32_t minPoints)
{
    auto* combinations = new Points[minPoints];
    generateAllCombinationsOfCoreSet(coreSet.getPoints(), combinations, 0, (uint32_t) coreSet.getPoints().size() - 1, 0, minPoints);

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
