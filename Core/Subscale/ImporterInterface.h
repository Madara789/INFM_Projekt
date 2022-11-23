#pragma once

#include "Importer/Dimension.h"
#include "DataLabelerInterface.h"

class ImporterInterface {
public:
	virtual std::tuple<Dimensions, uint64_t, uint64_t> import(DataLabelerInterface*) = 0;
    virtual ~ImporterInterface() = default;
};