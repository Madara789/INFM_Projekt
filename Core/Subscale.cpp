#include "Subscale.h"

#include <vector>

Subscale::Subscale(
	CoreSetSeekerInterface coreSetSeeker,
	DenseUnitGeneratorInterface denseUnitGenerator,
	SubspaceDetectorInterface subspaceDetector,
	SubspaceCombinerInterface subspaceCombiner
) : coreSetSeeker_(coreSetSeeker),
	denseUnitGenerator_(denseUnitGenerator),
	subspaceDetector_(subspaceDetector),
	subspaceCombiner_(subspaceCombiner)
{}

Clusters Subscale::getClusters(Dimensions dimensions) {
	std::vector<CoreSets> allCoreSets;
	for (Dimension dimension : dimensions) {
		allCoreSets.push_back(this->coreSetSeeker_.getCoreSets(dimension);
	}

	DenseUnits denseUnits = DenseUnits();
	for (CoreSets coreSets : allCoreSets) {
		DenseUnits denseUnitsOfDimension = this->denseUnitGenerator_.getDenseUnits(coreSets);
		denseUnits.insert(denseUnits.end(), denseUnitsOfDimension.begin(), denseUnitsOfDimension.end());
	}

	Subspaces subspaces = this->subspaceDetector_.detectSubspaces(denseUnits);

	return this->subspaceCombiner_.getClusters(subspaces);
}