#pragma once

#include <vector>

#include "Data/DataSet.h"
#include "Data/Cluster.h"
#include "Subscale/DataLabelerInterface.h"
#include "Subscale/CoreSetGeneratorInterface.h"
#include "Subscale/DenseUnitGeneratorInterface.h"

class Subscale
{
private:
	DataLabelerInterface* dataLabeler_;
	CoreSetGeneratorInterface* coreSetGenerator_;
	DenseUnitGeneratorInterface* denseUnitGenerator_;

public:
	Subscale(DataLabelerInterface*, CoreSetGeneratorInterface*, DenseUnitGeneratorInterface*);
	~Subscale();
	Clusters getClusters(DataSet);
};