#include "CsvClusterExporter.h"

#include <iostream>

CsvClusterExporter::CsvClusterExporter(std::string filePath, Clusters clusters) 
    : CsvExporter(filePath)
    {
        clusters_ = clusters;
    }

void CsvClusterExporter::doExport() {

    ensureDirectoryExists();

    const auto bufferSize = 50000000;
    auto buffer = new char[bufferSize];

    // Create an output filestream object
	std::ofstream myFile(filePath_.c_str());

	unsigned int bufferIndex = 0;
	int len;

    for (auto &&cluster : clusters_)
	{
		auto &&dimensions = cluster.getDimensions();
        auto &&points = cluster.getPoints();

        buffer[bufferIndex++] = '[';

		// Dimensions
		for (int j = 0; j < dimensions.size() - 1; j++)
		{
			len = sprintf(buffer + bufferIndex, "%I32u", dimensions[j]);
			bufferIndex += len;
			buffer[bufferIndex++] = ',';
		}

		// last dimension value (isn't followed by a comma)
		len = sprintf(buffer + bufferIndex, "%I32u", dimensions[dimensions.size() - 1]);
		bufferIndex += len;

		// closing bracket for dimensions and opening bracket for ids
		buffer[bufferIndex++] = ']';
		buffer[bufferIndex++] = '-';
		buffer[bufferIndex++] = '[';


		// IDs
		for (int j = 0; j < points.size() - 1; j++)
		{
			len = sprintf(buffer + bufferIndex, "%I64u", points[j]->getSignature());
			bufferIndex += len;
			buffer[bufferIndex++] = ',';
		}

		// last id value (isn't followed by a comma)
		len = sprintf(buffer + bufferIndex, "%I64u", points[points.size() - 1]->getSignature());
		bufferIndex += len;

		// closing bracket for ids and start new line
		buffer[bufferIndex++] = ']';
		buffer[bufferIndex++] = '\n';

	}

	myFile.write(buffer, bufferIndex);

	// Close the file
	myFile.close();
	
    delete[] buffer;
}