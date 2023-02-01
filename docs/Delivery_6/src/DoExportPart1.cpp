#include <fstream>
#include <string>

void CsvClusterExporter::doExport() {
    ensureDirectoryExists();
    const auto bufferSize = 50000000;
    auto buffer = new char[bufferSize];
	std::ofstream myFile(filePath_.c_str());
	unsigned int bufferIndex = 0;
	int len;
    // [...]
}