#pragma once

#include "../CoreSetGeneratorInterface.h"

class SequentialCoreSetGenerator : public CoreSetGeneratorInterface
{
	CoreSets getCoreSets(DataSet);
};