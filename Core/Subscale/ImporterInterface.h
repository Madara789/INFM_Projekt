#pragma once

#include "Importer/Dimension.h"
#include <vector>
#include <tuple>

class ImporterInterface {
public:
	virtual std::tuple<Dimensions, uint64_t, uint64_t>  import(uint32_t) = 0;
};