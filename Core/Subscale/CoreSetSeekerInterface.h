#pragma once

#include "CoreSetSeeker/CoreSet.h"
#include "Importer/Dimension.h"

class CoreSetSeekerInterface {
public:
	virtual CoreSets getCoreSets(Dimension dimension) = 0;
};