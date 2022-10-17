#pragma once

#include <vector>

#include "../Data/CoreSet.h"
#include "../Data/DataSet.h"

class CoreSetGeneratorInterface
{
public:
	virtual CoreSets getCoreSets(DataSet) = 0;
};