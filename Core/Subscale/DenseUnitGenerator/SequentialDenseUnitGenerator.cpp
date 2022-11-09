#include "SequentialDenseUnitGenerator.h"
#include <iostream>
#include <bits/stdc++.h>

DenseUnits &SequentialDenseUnitGenerator::getDenseUnits(const CoreSets &coreSets, const uint32_t minPoints)
{
    auto denseUnits = new DenseUnits();

    for (const auto &coreSet : coreSets)
    {
        DenseUnits denseUnitsOfCoreSet = generateDenseUnits(coreSet, minPoints);
        denseUnits->insert(denseUnits->end(), denseUnitsOfCoreSet.begin(), denseUnitsOfCoreSet.end());
    }

    return *denseUnits;
}

DenseUnits SequentialDenseUnitGenerator::generateDenseUnits(const CoreSet &coreSet, const uint32_t minPoints)
{
    Points *combinations = new Points[minPoints];
    DenseUnits denseUnitsOfCoreSet;

    calculateCombinations(coreSet.getPoints(), combinations, minPoints);

    auto *iterator = combinations;
    for (uint32_t i = 0; i < minPoints; i++)
    {
        uint64_t signature = calculateSignature(*iterator);

        denseUnitsOfCoreSet.push_back(DenseUnit(*iterator, signature, coreSet.getDimension()));

        ++iterator;
    }

    return denseUnitsOfCoreSet;
}

void SequentialDenseUnitGenerator::calculateCombinations(const Points &points, Points combinations[], const uint32_t minPoints)
{
    uint32_t depth = minPoints - 1;
    uint32_t pointIndex = points.size() - 1;

    if (depth > pointIndex)
        return;

    Points *tmpCombination = generateTmpPoints(minPoints);

    tmpCombination->at(depth) = points[pointIndex];

    while (true)
    {
        fillCombinationToLeft(tmpCombination, points, depth, pointIndex);

        addNewCombination(combinations, tmpCombination);

        while (replaceCombinationWithNewPoint(tmpCombination, depth, points, pointIndex) && depth == pointIndex)
        {

            addNewCombination(combinations, tmpCombination);

            if (++depth == minPoints)
            {
                std::cout << "done with " << combinations->size() << " from " << points.size() << std::endl;
                delete[] tmpCombination;
                return;
            }

            calculateNewPointIndex(pointIndex, depth, tmpCombination, points);
        }
    }
}

Points *SequentialDenseUnitGenerator::generateTmpPoints(const uint32_t minPoints)
{
    Points *tmpCombination = new Points[minPoints];

    for (int i = 0; i < minPoints; i++)
    {
        tmpCombination->push_back(new Point(5, 5));
    }

    return tmpCombination;
}

void SequentialDenseUnitGenerator::fillCombinationToLeft(Points tmpCombination[], const Points &points, uint32_t &depth, uint32_t &pointIndex)
{
    while (depth)
    {
        tmpCombination->at(--depth) = points[--pointIndex];
    }
}

void SequentialDenseUnitGenerator::addNewCombination(Points combinations[], const Points tmpCombination[])
{
    combinations->insert(combinations->end(), tmpCombination->begin(), tmpCombination->end());
}

bool SequentialDenseUnitGenerator::replaceCombinationWithNewPoint(Points tmpCombination[], unsigned int &depth, const Points &points, unsigned int &pointIndex)
{
    tmpCombination->at(depth) = points[--pointIndex];
    return true;
}

void SequentialDenseUnitGenerator::calculateNewPointIndex(uint32_t &pointIndex, uint32_t &depth, const Points tmpCombination[], const Points &points)
{
    pointIndex = find(points.begin(), points.end(), tmpCombination->at(depth)) - points.begin();
}

uint64_t SequentialDenseUnitGenerator::calculateSignature(const Points &points)
{
    uint64_t signature = 0;
    for (auto point : points)
    {
        signature += point->getSignature();
    }
    return signature;
}

/* TODO remove
    std::cout << pointIndex << ", " << depth << std::endl;
    for (int i = pointIndex; i >= 0; i--)
        std::cout << points.at(i)->getValue() << ",";
    std::cout << std::endl;
    for (int i = 0; i < 3; i++)
        std::cout << tmpCombination->at(i)->getValue() << ",";
    std::cout << std::endl;
    std::cout << pointIndex << ", " << depth << std::endl;
*/