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
	CoreSetSeekerInterface* coreSetSeeker;
	DenseUnitGeneratorInterface* denseUnitGenerator;
	SubspaceDetectorInterface* subspaceDetector;
	SubspaceCombinerInterface* subspaceCombiner;

public:
	Subscale(
		CoreSetSeekerInterface* coreSetSeeker,
		DenseUnitGeneratorInterface* denseUnitGenerator,
		SubspaceDetectorInterface* subspaceDetector,
		SubspaceCombinerInterface* subspaceCombiner
	);
	Clusters getClusters(Dimensions dimensions);
};