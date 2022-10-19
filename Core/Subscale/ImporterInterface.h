#pragma once

#include "Importer/Dimension.h"

class ImporterInterface {
public:
	virtual Dimensions import() = 0;
};