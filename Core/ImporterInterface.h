#pragma once

#include "Data/Dimension.h"

class ImporterInterface
{
public:
	virtual Dimensions getDimensions() = 0;
    virtual int32_t getSubspaceEntries() = 0;
};