#pragma once

#include "../CoreSetGeneratorInterface.h"
#include "CoreSet.h"
#include "../Importer/Dimension.h"

class SequentialCoreSetGenerator : public CoreSetGeneratorInterface {
private:
	int minPoints_;
	double epsilon_;

public:
	SequentialCoreSetGenerator(int minPoints, double epsilon);
	CoreSets getCoreSets(Dimensions);
};