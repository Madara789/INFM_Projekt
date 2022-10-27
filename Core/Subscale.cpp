#include "Subscale.h"

#include <vector>
#include <iostream>
#include <chrono>

Subscale::Subscale(
	CoreSetSeekerInterface* coreSetSeeker,
	DenseUnitGeneratorInterface* denseUnitGenerator,
	SubspaceDetectorInterface* subspaceDetector,
	SubspaceCombinerInterface* subspaceCombiner
) : coreSetSeeker(coreSetSeeker),
    denseUnitGenerator(denseUnitGenerator),
    subspaceDetector(subspaceDetector),
    subspaceCombiner(subspaceCombiner)
{}

Clusters Subscale::getClusters(Dimensions dimensions) {
	std::vector<CoreSets> allCoreSets;
    std::cout << "creating CoreSets \n";
	for (const Dimension& dimension : dimensions) {
        allCoreSets.push_back(coreSetSeeker->getCoreSets(dimension));
	}

    allCoreSets.shrink_to_fit();
    std::cout << allCoreSets.size() << "\n";

    std::cout << "creating DenseUnits for all CoreSets \n";
    DenseUnits denseUnits = DenseUnits();
	for (const CoreSets& coreSets : allCoreSets) {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		DenseUnits denseUnitsOfDimension = this->denseUnitGenerator->getDenseUnits(coreSets, 3); // FIXME minPoints through config
        std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - begin).count() << "s" << std::endl;
		denseUnits.insert(denseUnits.end(), denseUnitsOfDimension.begin(), denseUnitsOfDimension.end());
	}

	Subspaces subspaces = this->subspaceDetector->detectSubspaces(denseUnits);

	return this->subspaceCombiner->getClusters(subspaces);
}