#include "Subscale.h"

#include <vector>
#include <iostream>
#include <chrono>
#include "Helper/Config.h"

Subscale::Subscale(
    CoreSetSeekerInterface *coreSetSeeker,
    DenseUnitGeneratorInterface *denseUnitGenerator,
    SubspaceDetectorInterface *subspaceDetector,
    SubspaceCombinerInterface *subspaceCombiner) : coreSetSeeker(coreSetSeeker), denseUnitGenerator(denseUnitGenerator), subspaceDetector(subspaceDetector), subspaceCombiner(subspaceCombiner)
{
}

Clusters Subscale::getClusters(const Dimensions &dimensions)
{

    std::vector<CoreSets> allCoreSets;
    std::cout << "creating CoreSets \n";
    for (const Dimension &dimension : dimensions)
    {
        allCoreSets.push_back(coreSetSeeker->getCoreSets(dimension));
    }

    allCoreSets.shrink_to_fit();
    std::cout << allCoreSets.size() << "\n";

    std::cout << "creating DenseUnits for all CoreSets \n";
    DenseUnits denseUnits;
    for (auto coreSets : allCoreSets)
    {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        DenseUnits denseUnitsOfDimension = this->denseUnitGenerator->getDenseUnits(coreSets, Config::get()->getMinPoints(), 0, 0);
        std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - begin).count() << "s" << std::endl;
        denseUnits.insert(denseUnits.end(), denseUnitsOfDimension.begin(), denseUnitsOfDimension.end());
        coreSets.clear();
    }
    allCoreSets.clear();

    Subspaces subspaces = this->subspaceDetector->detectSubspaces(denseUnits);

    return this->subspaceCombiner->getClusters(subspaces);
}

Subspaces Subscale::getSubspaceTable(const Dimensions &dimensions, uint64_t min, uint64_t max)
{
    std::vector<CoreSets> allCoreSets;
    std::cout << "creating CoreSets \n";
    for (const Dimension &dimension : dimensions)
    {
        allCoreSets.push_back(coreSetSeeker->getCoreSets(dimension));
    }

    allCoreSets.shrink_to_fit();
    std::cout << allCoreSets.size() << "\n";

    std::cout << "creating DenseUnits for bounds min: " << min << " and max: " << max << std::endl;
    DenseUnits denseUnits;
    for (auto coreSets : allCoreSets)
    {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        DenseUnits denseUnitsOfDimension = this->denseUnitGenerator->getDenseUnits(coreSets, 3, min, max);
        std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - begin).count() << "s" << std::endl;
        denseUnits.insert(denseUnits.end(), denseUnitsOfDimension.begin(), denseUnitsOfDimension.end());
        coreSets.clear();
    }
    allCoreSets.clear();

    Subspaces subspaces = this->subspaceDetector->detectSubspaces(denseUnits);

    return subspaces;
}