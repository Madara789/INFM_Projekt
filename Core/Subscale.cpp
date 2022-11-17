#include "Subscale.h"

#include <vector>
#include <iostream>
#include <chrono>

Subscale::Subscale(
        DataLabelerInterface* dataLabeler,
        CoreSetSeekerInterface* coreSetSeeker,
        DenseUnitGeneratorInterface* denseUnitGenerator,
        SubspaceDetectorInterface* subspaceDetector,
        SubspaceCombinerInterface* subspaceCombiner
        ) : dataLabeler(dataLabeler), coreSetSeeker(coreSetSeeker), denseUnitGenerator(denseUnitGenerator), subspaceDetector(subspaceDetector), subspaceCombiner(subspaceCombiner)
{}

Clusters Subscale::getClusters(const Dimensions& dimensions) {
    auto minMaxTuple = this->dataLabeler->label(dimensions);
    std::cout << "Min Signature: " << std::get<0>(minMaxTuple) << " Max Signature: " << std::get<1>(minMaxTuple) << std::endl;

	std::vector<CoreSets> allCoreSets;
    std::cout << "creating CoreSets \n";
	for (const Dimension& dimension : dimensions) {
        allCoreSets.push_back(coreSetSeeker->getCoreSets(dimension));
    }

    allCoreSets.shrink_to_fit();
    std::cout << allCoreSets.size() << "\n";

    std::cout << "creating DenseUnits for all CoreSets \n";
    DenseUnits denseUnits;
	for (auto coreSets : allCoreSets) {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		DenseUnits denseUnitsOfDimension = this->denseUnitGenerator->getDenseUnits(coreSets, 3); // FIXME minPoints through config
        std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - begin).count() << "s" << std::endl;
		denseUnits.insert(denseUnits.end(), denseUnitsOfDimension.begin(), denseUnitsOfDimension.end());
        coreSets.clear();
    }
    allCoreSets.clear();

	Subspaces subspaces = this->subspaceDetector->detectSubspaces(denseUnits);

	return this->subspaceCombiner->getClusters(subspaces);
}