#pragma once

#include "../ImporterInterface.h"
#include "../DataLabeler/SequentialDataLabeler.h"

#include <fstream>
#include <vector>

class CsvImporter : public ImporterInterface {
private:
	const char* filePath_;
	LabelGenerator* labelGenerator_;

public:
	CsvImporter(const char* filePath, LabelGenerator* labelGenerator);
	std::tuple<Dimensions, uint64_t, uint64_t> import(uint32_t);

private:
	std::ifstream* getFileStream();
	std::vector<std::vector<double_t>> getCsvRows(std::ifstream* input);
};