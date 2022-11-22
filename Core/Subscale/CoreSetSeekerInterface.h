#pragma once

#include "CoreSetSeeker/CoreSet.h"
#include "Importer/Dimension.h"

class CoreSetSeekerInterface {
public:
	virtual CoreSets &getCoreSets(const Dimension& dimension) = 0;
    virtual ~CoreSetSeekerInterface() = default;
};