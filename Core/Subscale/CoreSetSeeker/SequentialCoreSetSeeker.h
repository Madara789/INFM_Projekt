#pragma once

#include "../CoreSetSeekerInterface.h"
#include "CoreSet.h"
#include "../Importer/Dimension.h"

class SequentialCoreSetGenerator : public CoreSetSeekerInterface {
private:
	int minPoints_;
	double epsilon_;

public:
	SequentialCoreSetGenerator(int minPoints, double epsilon);
	CoreSets getCoreSets(Dimension dimension) override;
};