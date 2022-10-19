#pragma once

#include "../SubspaceDetectorInterface.h"

class SequentialSubspaceDetector : public SubspaceDetectorInterface {
public:
	Subspaces detectSubspaces(DenseUnits);
};