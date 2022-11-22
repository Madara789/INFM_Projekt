#include "CsvImporter.h"

#include "Point.h"

#include <string>
#include <sstream>
#include <iostream>

CsvImporter::CsvImporter(
	const char *filePath,
	LabelGenerator *labelGenerator) : filePath_(filePath), labelGenerator_(labelGenerator) {}

std::tuple<Dimensions, uint64_t, uint64_t> CsvImporter::import(uint32_t minPoints)
{
	std::ifstream *input = this->getFileStream();
	std::vector<std::vector<double_t>> csvRows = this->getCsvRows(input);
	input->close();

	const auto numberOfPoints = csvRows.size();

	// variables
	auto labels = std::vector<unsigned long long>();
	labels.reserve(numberOfPoints);
	unsigned long long minSignature;
	unsigned long long maxSignature;

	// generate labels
	labelGenerator_->getLabelsForVector(labels, numberOfPoints);
	minSignature = labelGenerator_->calcMinSignatureFromVector(labels, numberOfPoints, minPoints);
	maxSignature = labelGenerator_->calcMaxSignatureFromVector(labels, numberOfPoints, minPoints);
	delete labelGenerator_;

	size_t amountDimensions = csvRows[0].size();
	Dimensions dimensions = Dimensions();
	dimensions.reserve(amountDimensions);

	for (size_t i = 0; i < amountDimensions; i++)
	{
		Points points = Points();
		uint16_t rowIndex = 0;
		for (int j = 0; j < numberOfPoints; j++)
		{
			points.push_back(new Point(csvRows[j][rowIndex], labels[j]));
		}
		rowIndex++;
		dimensions.push_back(Dimension(rowIndex, points));
	}
	return {dimensions, minSignature, maxSignature};
}

std::ifstream *CsvImporter::getFileStream()
{
	auto *input = new std::ifstream(this->filePath_);
	if (!input->is_open())
	{
		char *errorMessage = new char;
		sprintf(errorMessage, "Could not read file: %s", this->filePath_);

		throw std::runtime_error(errorMessage);
	}

	return input;
}

std::vector<std::vector<double_t>> CsvImporter::getCsvRows(std::ifstream *input)
{
	std::vector<std::vector<double_t>> csvRows;

	std::string row;
	while (std::getline(*input, row))
	{
		std::stringstream ss = std::stringstream(row);
		std::vector<double_t> values;
		double_t value;
		while (ss >> value)
		{
			values.push_back(value);
			if (ss.peek() == ',')
			{
				ss.ignore();
			}
		}
		values.shrink_to_fit();
		csvRows.push_back(values);
	}

	csvRows.shrink_to_fit();

	return csvRows;
}