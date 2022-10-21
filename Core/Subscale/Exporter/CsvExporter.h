#pragma once 

#include "../ExporterInterface.h"
#include <string>

class CsvExporter : public ExporterInterface
{
protected:
    std::string filePath_;

public:
    CsvExporter(std::string filePath);
    virtual void doExport() = 0;

protected:
    void ensureDirectoryExists();
};

