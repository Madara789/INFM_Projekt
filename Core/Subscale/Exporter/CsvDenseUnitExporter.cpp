#include "CsvDenseUnitExporter.h"

#include <utility>
#include <iostream>
#include <fstream>

CsvDenseUnitExporter::CsvDenseUnitExporter(std::string filePath, DenseUnits &denseUnits): CsvExporter(std::move(filePath)), denseUnits(denseUnits)
{}

void CsvDenseUnitExporter::doExport()
{
    ensureDirectoryExists();

    const auto bufferSize = 50000000;
    auto buffer = new char[bufferSize];

    std::ofstream file(filePath_.c_str());

    unsigned int bufferIndex = 0;
    int len;

    // signature, dimension, [[Point.signature(), Point.value()], ..]
    for (auto denseUnit : denseUnits)
    {
        if (denseUnit.getPoints().size() <= 1)
            continue;

        len = sprintf(buffer + bufferIndex, "%I64u", denseUnit.getSignature());
        bufferIndex +=len;
        buffer[bufferIndex++] = ',';

        len = sprintf(buffer + bufferIndex, "%I32u", denseUnit.getDimension());
        bufferIndex +=len;
        buffer[bufferIndex++] = ',';


        buffer[bufferIndex++] = '[';
        for (int i = 0; i < denseUnit.getPoints().size() - 1; i++)
        {
            len = sprintf(buffer + bufferIndex, "[%I64u, %f]", denseUnit.getPoints()[i]->getSignature(), denseUnit.getPoints()[i]->getValue());
            bufferIndex += len;
            buffer[bufferIndex++] = ',';
        }

        len = sprintf(buffer + bufferIndex, "[%I64u, %f]", denseUnit.getPoints()[denseUnit.getPoints().size() - 1]->getSignature(), denseUnit.getPoints()[denseUnit.getPoints().size() - 1]->getValue());
        bufferIndex += len;

        buffer[bufferIndex++] = ']';
        buffer[bufferIndex++] = '\n';
    }

    file.write(buffer, bufferIndex);
    file.close();
    delete[] buffer;
}
