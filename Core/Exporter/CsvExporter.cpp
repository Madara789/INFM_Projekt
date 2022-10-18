#include "CsvExporter.h"

CsvExporter::CsvExporter(const char *filePath): filePath(filePath){}

CsvExporter::~CsvExporter()
{
    delete filePath;
}

void CsvExporter::exportSubspaceTable(const Subspace &subspace)
{

}

void CsvExporter::exportVectorTable(const Subspace &subspace)
{

}

void CsvExporter::exportClusters(const Cluster &cluster)
{

}
