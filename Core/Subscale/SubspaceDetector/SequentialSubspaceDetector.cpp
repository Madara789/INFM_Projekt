#include "SequentialSubspaceDetector.h"

Subspaces SequentialSubspaceDetector::detectSubspaces(DenseUnits denseUnits) {
    Subspaces subspaces;
    for (const auto& denseUnit : denseUnits)
    {
        if (!subspaces.contains(denseUnit.getSignature())) {
            subspaces[denseUnit.getSignature()] = new Subspace(denseUnit);
            continue;
        }

        auto subspace = subspaces[denseUnit.getSignature()];
        subspace->addDenseUnit(denseUnit);
    }

	return subspaces;
}