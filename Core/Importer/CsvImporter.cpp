#include "CsvImporter.h"

#include <fstream>
#include <string>
#include <vector>

CsvImporter::CsvImporter(
	char* filePath
) : filePath_(filePath) {}

CsvImporter::~CsvImporter() {
	delete this->filePath_;
}

Dimensions CsvImporter::getDimensions() {
	std::ifstream csvFile(this->filePath_);
	if (!csvFile.is_open())
		throw std::runtime_error("Could not open file");

	Dimensions dimensions = Dimensions();
	std::string line;

	std::vector<std::vector<double>> csvData = std::vector<std::vector<double>>();
	while (std::getline(csvFile, line)) {

	}

	return dimensions;
}