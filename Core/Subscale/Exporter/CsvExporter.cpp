
#include "CsvExporter.h"

#include <filesystem>

CsvExporter::CsvExporter(std::string filePath)
    : filePath_(filePath)
{
}

void CsvExporter::ensureDirectoryExists()
{
    uint32_t pos = filePath_.find_last_of("\\/");
    if (std::string::npos == pos)
        return;

    auto dirPath = filePath_.substr(0, pos);

    if (!std::filesystem::is_directory(dirPath) || !std::filesystem::exists(dirPath))
    {                                             // Check if src folder exists
        std::filesystem::create_directory(dirPath); // create src folder
    }
}
