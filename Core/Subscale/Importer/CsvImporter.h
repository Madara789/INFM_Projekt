#pragma once

#include "../ImporterInterface.h"

#include <fstream>
#include <vector>

class CsvImporter : public ImporterInterface {
private:
	const char* filePath_;

public:
	explicit CsvImporter(const char* filePath);
    std::tuple<Dimensions, uint64_t, uint64_t> import(DataLabelerInterface*) override;
    ~CsvImporter() override = default;

private:
	std::ifstream* getFileStream();
	std::vector<std::vector<double_t>> getCsvRows(std::ifstream* input);
};