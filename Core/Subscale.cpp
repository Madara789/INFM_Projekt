#include "Subscale.h"

#include <vector>

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
	for (Dimension dimension : dimensions) {
        allCoreSets.push_back(coreSetSeeker->getCoreSets(dimension));
	}

	DenseUnits denseUnits = DenseUnits();
	for (CoreSets coreSets : allCoreSets) {
		DenseUnits denseUnitsOfDimension = this->denseUnitGenerator->getDenseUnits(coreSets);
		denseUnits.insert(denseUnits.end(), denseUnitsOfDimension.begin(), denseUnitsOfDimension.end());
	}

	Subspaces subspaces = this->subspaceDetector->detectSubspaces(denseUnits);

	return this->subspaceCombiner->getClusters(subspaces);
}

Clusters Subscale::createDummyClusters() {
	return this->subspaceCombiner->createDummyClusters();
}