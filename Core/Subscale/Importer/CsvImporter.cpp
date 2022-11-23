#include "CsvImporter.h"

#include "Point.h"

#include <string>
#include <sstream>

CsvImporter::CsvImporter(
	const char* filePath
) : filePath_(filePath) {}

std::tuple<Dimensions, uint64_t, uint64_t> CsvImporter::import(DataLabelerInterface* dataLabeler) {
    std::ifstream *input = this->getFileStream();
    std::vector<std::vector<double_t>> csvRows = this->getCsvRows(input);
    input->close();

    const auto numberOfPoints = csvRows.size();

    auto labeledData = dataLabeler->label(numberOfPoints);
    unsigned long long minSignature = labeledData->getMinSignature();
    unsigned long long maxSignature = labeledData->getMaxSignature();

    size_t amountDimensions = csvRows[0].size();
    Dimensions dimensions = Dimensions();
    dimensions.reserve(amountDimensions);

    for (size_t i = 0; i < amountDimensions; i++)
    {
        Points points = Points();
        for (int j = 0; j < numberOfPoints; j++)
        {
            points.push_back(new Point(csvRows[j][i], labeledData->getLabels()[j]));
        }
        dimensions.push_back(Dimension(i + 1, points));
    }

    delete input;
    return { dimensions, minSignature, maxSignature };
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