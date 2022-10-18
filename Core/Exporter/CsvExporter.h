#ifndef SUBSCALE_CSVEXPORTER_H
#define SUBSCALE_CSVEXPORTER_H


#include "../ExporterInterface.h"

class CsvExporter : ExporterInterface
{
private:
    const char* filePath;

public:
    CsvExporter(const char* filePath);
    ~CsvExporter();

    void exportSubspaceTable(const Subspace& subspace) override;
    void exportVectorTable(const Subspace& subspace) override;
    void exportClusters(const Cluster& cluster) override;
};


#endif
