#include "SequentialCoreSetSeeker.h"

#include <cmath>

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
CoreSets SequentialCoreSetGenerator::getCoreSets(Dimension dimension) {
    CoreSets coreSets;

    for (int32_t i = 0; i < dimension.getSize(); i++) {
        Point* referencePoint = dimension.getPoint(i);
        CoreSet coreSet;
        coreSet.addPoint(referencePoint);

        for (int32_t j = i + 1; j < dimension.getSize(); j++) {
            Point* investigatedPoint = dimension.getPoint(j);
            if (std::abs(referencePoint - investigatedPoint) < this->epsilon_) {
                coreSet.addPoint(investigatedPoint);
            }
        }

        if (coreSet.getSize() >= this->minPoints_) {
            coreSets.push_back(coreSet);
        }
    }

    coreSets.shrink_to_fit();

    return coreSets;
}