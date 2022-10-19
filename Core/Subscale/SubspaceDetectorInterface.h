#pragma once

#include "SubspaceDetector/Subspace.h"
#include "DenseUnitGenerator/DenseUnit.h"

class SubspaceDetectorInterface {
public:
	virtual Subspaces detectSubspaces(DenseUnits) = 0;
};