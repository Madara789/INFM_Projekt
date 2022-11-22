#pragma once

#include "Subscale/CoreSetSeekerInterface.h"
#include "Subscale/DenseUnitGeneratorInterface.h"
#include "Subscale/SubspaceDetectorInterface.h"
#include "Subscale/SubspaceCombinerInterface.h"
#include "Subscale/Cluster.h"
#include "Subscale/Importer/Dimension.h"
#include "Subscale/DataLabelerInterface.h"
#include "Subscale/DenseUnitCombinerInterface.h"

class Subscale
{
private:
    DataLabelerInterface* dataLabeler;
	CoreSetSeekerInterface* coreSetSeeker;
	DenseUnitGeneratorInterface* denseUnitGenerator;
    DenseUnitCombinerInterface* denseUnitCombiner;
	SubspaceDetectorInterface* subspaceDetector;
	SubspaceCombinerInterface* subspaceCombiner;

public:
	Subscale(
            DataLabelerInterface* dataLabelerInterface,
            CoreSetSeekerInterface* coreSetSeeker,
            DenseUnitGeneratorInterface* denseUnitGenerator,
            DenseUnitCombinerInterface* denseUnitCombiner,
            SubspaceDetectorInterface* subspaceDetector,
            SubspaceCombinerInterface* subspaceCombiner
            );
	Clusters getClusters(Dimensions& dimensions);
};