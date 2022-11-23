#include "SequentialCoreSetSeeker.h"

#include <cmath>
#include <iostream>

SequentialCoreSetGenerator::SequentialCoreSetGenerator(
    int minPoints,
    double epsilon
): minPoints_(minPoints), epsilon_(epsilon) {}

/**
 * Calculates all CoreSets for a Dimension
 * 
 * @param dimension - The dimension for which all CoreSets should be calculated
 * 
 * @return All CoreSets which were indentified in the Dimension
 */
CoreSets &SequentialCoreSetGenerator::getCoreSets(const Dimension &dimension) {
    auto coreSets = new CoreSets();

    for (int32_t i = 0; i < dimension.getPoints().size(); i++) {
        Point* referencePoint = dimension.getPoints()[i];
        CoreSet coreSet(dimension.getId());
        coreSet.addPoint(referencePoint);

        for (int32_t j = i + 1; j < dimension.getPoints().size(); j++) {
            Point* investigatedPoint = dimension.getPoints()[j];
            if (std::abs(referencePoint->getValue() - investigatedPoint->getValue()) < this->epsilon_) {
//            if (referencePoint->getValue() - investigatedPoint->getValue() <= this->epsilon_) {
                coreSet.addPoint(investigatedPoint);
            }
        }

        if (coreSet.getPoints().size() >= this->minPoints_) {
            coreSets->push_back(coreSet);
        }
    }

    coreSets->shrink_to_fit();

    return *coreSets;
}