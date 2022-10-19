#pragma once

#include "Cluster.h"
#include "SubspaceDetector/Subspace.h"

class SubspaceCombinerInterface {
public:
	virtual Clusters getClusters(Subspaces) = 0;
};