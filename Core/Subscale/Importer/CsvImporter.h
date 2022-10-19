#pragma once

#include "../ImporterInterface.h"

class CsvImporter : public ImporterInterface {
public:
	Dimensions import();
};