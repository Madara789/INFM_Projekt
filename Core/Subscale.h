#pragma once

#include "Subscale/CoreSetSeekerInterface.h"
#include "Subscale/DenseUnitGeneratorInterface.h"
#include "Subscale/SubspaceDetectorInterface.h"
#include "Subscale/SubspaceCombinerInterface.h"
#include "Subscale/Cluster.h"
#include "Subscale/Importer/Dimension.h"

class Subscale
{
private:
	CoreSetSeekerInterface coreSetSeeker_;
	DenseUnitGeneratorInterface denseUnitGenerator_;
	SubspaceDetectorInterface subspaceDetector_;
	SubspaceCombinerInterface subspaceCombiner_;

public:
	Subscale(
		CoreSetSeekerInterface,
		DenseUnitGeneratorInterface,
		SubspaceDetectorInterface,
		SubspaceCombinerInterface
	);
	Clusters getClusters(Dimensions);
};