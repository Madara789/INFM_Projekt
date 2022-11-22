#include "CsvImporter.h"

#include "Point.h"

#include <string>
#include <sstream>

CsvImporter::CsvImporter(
	const char* filePath
) : filePath_(filePath) {}

Dimensions CsvImporter::import() {
	std::ifstream* input = this->getFileStream();
	std::vector<std::vector<double_t>> csvRows = this->getCsvRows(input);
	input->close();

	size_t amountDimensions = csvRows[0].size();
	std::vector<Points> dimensions = std::vector<Points>(amountDimensions);

    uint32_t rowIndex = 0;
	for (std::vector<double_t> row : csvRows) {
		for (int i = 0; i < row.size(); i++) {
			dimensions[i].push_back(new Point(row[i], rowIndex));
		}
        rowIndex++;
	}

	Dimensions transformedDimensions;
	for (uint32_t i = 0; i < dimensions.size(); i++){
		transformedDimensions.push_back(Dimension(i + 1, dimensions[i]));
	}
	
    delete input;
	return transformedDimensions;
}

std::ifstream* CsvImporter::getFileStream() {
	auto* input = new std::ifstream(this->filePath_);
	if (!input->is_open()) {
		char* errorMessage = new char;
		sprintf(errorMessage, "Could not read file: %s", this->filePath_);

		throw std::runtime_error(errorMessage);
	}

    return input;
}

std::vector<std::vector<double_t>> CsvImporter::getCsvRows(std::ifstream* input) {
	std::vector<std::vector<double_t>> csvRows;

	std::string row;
	while (std::getline(*input, row)) {
		std::stringstream ss = std::stringstream(row);
		std::vector<double_t> values;
		double_t value;
		while (ss >> value) {
			values.push_back(value);
			if (ss.peek() == ',') {
				ss.ignore();
			}
		}
		values.shrink_to_fit();
		csvRows.push_back(values);
 	}

	csvRows.shrink_to_fit();

	return csvRows;
}