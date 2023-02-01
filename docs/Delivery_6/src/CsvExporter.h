#pragma once 
#include <string>

class CsvExporter {
protected:
    std::string filePath_;

public:
    CsvExporter(std::string filePath);
    virtual void doExport() = 0;
    
protected:
    void ensureDirectoryExists();
};