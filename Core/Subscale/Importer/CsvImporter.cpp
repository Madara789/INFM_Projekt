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

	for (std::vector<double_t> row : csvRows) {
		for (int i = 0; i < row.size(); i++) {
			dimensions[i].push_back(new Point(row[i], 1)); // TODO: Replace 1 by high number
		}
	}

	Dimensions transformedDimensions;
	for (Points dimension : dimensions) {
		transformedDimensions.push_back(Dimension(dimension));
	}

	return transformedDimensions;

	return Dimensions();
}

std::ifstream* CsvImporter::getFileStream() {
	std::ifstream* input = new std::ifstream(this->filePath_);
	if (!input->is_open()) {
		char* errorMessage = new char;
		std::sprintf(errorMessage, "Could not read file: %s", this->filePath_);

		throw std::runtime_error(errorMessage);
	}
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