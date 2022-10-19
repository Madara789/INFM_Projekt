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

    for (int i = 0; i < dimension.getSize(); i++) {
        Point referencePoint = dimension.getPoint(i);
        CoreSet coreSet(Points([referencePoint]);

        for (int j = i + 1; j < dimension.getSize(); j++) {
            Point investiagetedPoint = dimension.getPoint(j)
            if (std::abs(referencePoint - investiagetedPoint) < this->epsilon_) {
                coreSet.addPoint(investiagetedPoint);
            }
        }

        if (coreSet.getSize() >= this->minPoints_) {
            coreSets.push_back(coreSet);
        }
    }

    coreSets.shrink_to_fit();

    return coreSets;
}