#pragma once

#include "Cluster.h"
#include "SubspaceDetector/Subspace.h"

class SubspaceCombinerInterface {
public:
	virtual Clusters getClusters(Subspaces subspaces) = 0;
	virtual Clusters createDummyClusters() = 0;
};