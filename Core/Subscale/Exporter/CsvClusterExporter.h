#pragma once 

#include "CsvExporter.h"
#include "../Cluster.h"

#include <fstream>
#include <string>

class CsvClusterExporter : public CsvExporter
{
private:
   Clusters clusters_;
public:
    CsvClusterExporter(std::string, Clusters clusters);
    void doExport() override;
};

