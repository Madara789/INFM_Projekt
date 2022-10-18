#pragma once

#include "../ImporterInterface.h"

class CsvImporter : ImporterInterface
{
private:
	char* filePath_;

public:
	CsvImporter(char* filePath);
	~CsvImporter();
	Dimensions getDimensions() override;
    int32_t getSubspaceEntries() override;
};